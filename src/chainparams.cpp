// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2019 The PAWS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("000006fca67ca4d3faa905a44edb195555e58dfb5281b0169eb7e28cd681f366"))
    (10, uint256("000000d5638e4bec2d15b407ed5146dfb3bdff91bfeb3e9989bc11e1bf59d551"))
    (50, uint256("00000ee6ad23bfb8dcdcecc2258f31b2d3a6a95fd708dbb35bccf77865205e34"))
    (100, uint256("0000056e78d46af7aec54b0db8f41d4487b15c5347f099a37f994fcb179b2224"))
    (200, uint256("00000007db9e7b6634db5395ce290ea87b0b752114c5c30c886677bd1ea7fc92"))
    (500, uint256("cd999bd714b262caf78e4d812ff09e1d9b66d5c00ea0d9f2e0f382b01dc2beca"))
    (741, uint256("649f56a25ff17f5b09e073d3cb1769d57dc799c84e95267c38d7d983511d5f50"))
	;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1588418398, // * UNIX timestamp of last checkpoint block
    1296,    	 // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    3000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("000006fca67ca4d3faa905a44edb195555e58dfb5281b0169eb7e28cd681f366"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1588291200,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("000006fca67ca4d3faa905a44edb195555e58dfb5281b0169eb7e28cd681f366"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1588291200,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x0f;
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0x0e;
        pchMessageStart[3] = 0x1e;
        vAlertPubKey = ParseHex("04cb76285e728f416f457ffbb1b0ca52b59dbbf51bca1359085b103e18678abc8ff391c40f6019aaa823375d4509009f192738f972677e2cd7ae3ed395ecdef9c9");
        nDefaultPort = 18765;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // PAWS starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 4000000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60;
        nTargetSpacing = 2 * 60;
        nMaturity = 60;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 5000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1;
        nZerocoinStartHeight = 101;
        nAccumulatorStartHeight = 50;
        nZerocoinStartTime = 1529726034;
        nBlockEnforceSerialRange = 1;
        nBlockRecalculateAccumulators = ~1; 
        nBlockFirstFraudulent = ~1;
        nBlockLastGoodCheckpoint = ~1;

        const char* pszTimestamp = "May 1 2020 PAWS CRYO ReLaunch";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1588291200; // UTC May 1 2020 00:00:00
        genesis.nBits = 0x1E0FFFF0;
        genesis.nNonce = 4182720;

		hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("000006fca67ca4d3faa905a44edb195555e58dfb5281b0169eb7e28cd681f366"));
        assert(genesis.hashMerkleRoot == uint256("8b5c125823adc0d54444359efecf277beafa93f58051126f4869bac8fffdc41b"));

        vSeeds.push_back(CDNSSeedData("164.68.106.143", "164.68.106.143"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 117);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 120);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 80);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0xa2)(0x21)(0x14).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x22)(0xa1)(0xe1).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x02)(0x0a).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04e579d69c8f999dd6f37092846c972fe0a4c6972b5505f074588a16562965da76a5d78eae8b8e77d92827d774d320fac740173101fae301afc55c77709fe37117";
        strObfuscationPoolDummyAddress = "pJZRoFiiE3iVtGbafQouMzqx6iVhHmSQhD";
        nStartMasternodePayments = 1516371317;

        /** Zerocoin */
        zerocoinModulus = "09967519546633664161786592116176188244477851735247464471262506936419821425521535537971729591952844"
            "7993474316710383495651554441492284699784318317920768642771782479156335915769589065125381511877736478656163146112"
            "0274778749282514833787626065783543239214817635079109932062526589069357037529741126387254431354640890113819012884"
            "5984727198875027923684216536572545251927687617204175968296261497488347174940599536643486971848573156659145626196"
            "7823585489859811013117353687337255659905995864128249363763371577762942618252152391331762957988146692582388256324"
            "83429163614150572996214543792012965484479369325464648385288082629456952";
        nMaxZerocoinSpendsPerTransaction = 7; 
        nMinZerocoinMintFee = 1 * ZCENT; 
        nMintRequiredConfirmations = 20; 
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; 
        nZerocoinHeaderVersion = 4; 
        nBudget_Fee_Confirmations = 6; 

        nStakeMinConfirmations = 720;   
        nStakeMinAmount = 50 * COIN;    
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xfb;
        pchMessageStart[2] = 0xfc;
        pchMessageStart[3] = 0xfd;
        vAlertPubKey = ParseHex("04c1b4a7143a80e71bd6d57e293b3681d652b3ca1d04a1df987db15fe3ed886cc24578faaaf2f00ba216c1000bbbd00c4a63726b8f3370dc8a59949074de1f4f26");
        nDefaultPort = 18181;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; 
        nTargetSpacing = 2 * 60;  
        nLastPOWBlock = 200;
        nBTChangeBlock = 1000;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; 
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 50;
        nZerocoinStartTime = 1529726039;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint
        genesis.nTime = 1588291200;
        genesis.nNonce = 4182720;

	    hashGenesisBlock = genesis.GetHash();
	    assert(hashGenesisBlock == uint256("000006fca67ca4d3faa905a44edb195555e58dfb5281b0169eb7e28cd681f366"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet.paws.fund", "testnet.paws.fund"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 55);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 58);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 200);
        // Testnet paws BIP32 pubkeys
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x2a)(0x12)(0x11).convert_to_container<std::vector<unsigned char> >();
        // Testnet paws BIP32 prvkeys
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x41)(0x11)(0x1a).convert_to_container<std::vector<unsigned char> >();
        // Testnet paws BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04e579d69c8f999dd6f37092846c972fe0a4c6972b5505f074588a16562965da76a5d78eae8b8e77d92827d774d320fac740173101fae301afc55c77709fe37117";
        strObfuscationPoolDummyAddress = "pJZRoFiiE3iVtGbafQouMzqx6iVhHmSQhD";
        nStartMasternodePayments = 1420837558;
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nStakeMinConfirmations = 30;    // Required number of confirmations
        nStakeMinAmount = 1000 * COIN;  // Minimum required staking amount
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xf3;
        pchMessageStart[3] = 0xf4;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60;
        nTargetSpacing = 2 * 60;        
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1588291200;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 4182720;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 36210;
        assert(hashGenesisBlock == uint256("000006fca67ca4d3faa905a44edb195555e58dfb5281b0169eb7e28cd681f366"));

        vFixedSeeds.clear(); 
        vSeeds.clear();      

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
