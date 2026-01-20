
// Generated from src/grammar/cpp.g4 by ANTLR 4.12.0


#include "cppListener.h"

#include "cppParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CppParserStaticData final {
  CppParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CppParserStaticData(const CppParserStaticData&) = delete;
  CppParserStaticData(CppParserStaticData&&) = delete;
  CppParserStaticData& operator=(const CppParserStaticData&) = delete;
  CppParserStaticData& operator=(CppParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag cppParserOnceFlag;
CppParserStaticData *cppParserStaticData = nullptr;

void cppParserInitialize() {
  assert(cppParserStaticData == nullptr);
  auto staticData = std::make_unique<CppParserStaticData>(
    std::vector<std::string>{
      "start", "topLevelDecl", "classDecl", "classBody", "accessSpec", "classMember", 
      "fieldDecl", "ctorDecl", "methodDecl", "fnDecl", "params", "param", 
      "stmt", "vardecl", "assign", "exprStmt", "block", "whileStmt", "ifStmt", 
      "returnStmt", "expr", "assignExpr", "logicalOrExpr", "logicalAndExpr", 
      "equalityExpr", "relationalExpr", "additiveExpr", "multiplicativeExpr", 
      "unaryExpr", "postfixExpr", "memberAccess", "call", "args", "primaryExpr", 
      "literal", "type", "baseType"
    },
    std::vector<std::string>{
      "", "'class'", "':'", "'public'", "';'", "'{'", "'}'", "'('", "')'", 
      "'virtual'", "','", "'='", "'while'", "'if'", "'else'", "'return'", 
      "'||'", "'&&'", "'=='", "'!='", "'<'", "'>'", "'<='", "'>='", "'+'", 
      "'-'", "'*'", "'/'", "'%'", "'!'", "'.'", "'true'", "'false'", "'int'", 
      "'bool'", "'char'", "'string'", "'void'", "", "", "'&'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "ID", "NUMBER", "AMP", "CHAR", "STRING", "COMMENT_LINE", 
      "COMMENT_BLOCK", "PREPROC", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,46,324,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,1,0,1,0,5,0,77,8,0,10,0,12,0,80,9,0,1,0,1,0,1,1,1,1,3,1,
  	86,8,1,1,2,1,2,1,2,1,2,1,2,3,2,93,8,2,1,2,1,2,3,2,97,8,2,1,3,1,3,3,3,
  	101,8,3,1,3,5,3,104,8,3,10,3,12,3,107,9,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,
  	1,5,3,5,117,8,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,3,7,126,8,7,1,7,1,7,1,7,1,
  	8,3,8,132,8,8,1,8,1,8,1,8,1,8,3,8,138,8,8,1,8,1,8,1,8,3,8,143,8,8,1,9,
  	1,9,1,9,1,9,3,9,149,8,9,1,9,1,9,1,9,1,10,1,10,1,10,5,10,157,8,10,10,10,
  	12,10,160,9,10,1,11,1,11,3,11,164,8,11,1,11,1,11,1,12,1,12,1,12,1,12,
  	1,12,1,12,1,12,3,12,175,8,12,1,13,1,13,3,13,179,8,13,1,13,1,13,1,13,3,
  	13,184,8,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,16,1,
  	16,5,16,198,8,16,10,16,12,16,201,9,16,1,16,1,16,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,218,8,18,1,19,1,19,3,
  	19,222,8,19,1,19,1,19,1,20,1,20,1,21,1,21,1,22,1,22,1,22,5,22,233,8,22,
  	10,22,12,22,236,9,22,1,23,1,23,1,23,5,23,241,8,23,10,23,12,23,244,9,23,
  	1,24,1,24,1,24,5,24,249,8,24,10,24,12,24,252,9,24,1,25,1,25,1,25,5,25,
  	257,8,25,10,25,12,25,260,9,25,1,26,1,26,1,26,5,26,265,8,26,10,26,12,26,
  	268,9,26,1,27,1,27,1,27,5,27,273,8,27,10,27,12,27,276,9,27,1,28,1,28,
  	1,28,1,28,1,28,3,28,283,8,28,1,29,1,29,1,29,5,29,288,8,29,10,29,12,29,
  	291,9,29,1,30,1,30,1,30,1,31,1,31,3,31,298,8,31,1,31,1,31,1,32,1,32,1,
  	32,5,32,305,8,32,10,32,12,32,308,9,32,1,33,1,33,1,33,1,33,1,33,1,33,3,
  	33,316,8,33,1,34,1,34,1,35,1,35,1,36,1,36,1,36,0,0,37,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,
  	60,62,64,66,68,70,72,0,6,1,0,18,19,1,0,20,23,1,0,24,25,1,0,26,28,3,0,
  	31,32,39,39,41,42,1,0,33,38,327,0,78,1,0,0,0,2,85,1,0,0,0,4,87,1,0,0,
  	0,6,98,1,0,0,0,8,110,1,0,0,0,10,116,1,0,0,0,12,118,1,0,0,0,14,122,1,0,
  	0,0,16,131,1,0,0,0,18,144,1,0,0,0,20,153,1,0,0,0,22,161,1,0,0,0,24,174,
  	1,0,0,0,26,176,1,0,0,0,28,187,1,0,0,0,30,192,1,0,0,0,32,195,1,0,0,0,34,
  	204,1,0,0,0,36,210,1,0,0,0,38,219,1,0,0,0,40,225,1,0,0,0,42,227,1,0,0,
  	0,44,229,1,0,0,0,46,237,1,0,0,0,48,245,1,0,0,0,50,253,1,0,0,0,52,261,
  	1,0,0,0,54,269,1,0,0,0,56,282,1,0,0,0,58,284,1,0,0,0,60,292,1,0,0,0,62,
  	295,1,0,0,0,64,301,1,0,0,0,66,315,1,0,0,0,68,317,1,0,0,0,70,319,1,0,0,
  	0,72,321,1,0,0,0,74,77,3,2,1,0,75,77,3,24,12,0,76,74,1,0,0,0,76,75,1,
  	0,0,0,77,80,1,0,0,0,78,76,1,0,0,0,78,79,1,0,0,0,79,81,1,0,0,0,80,78,1,
  	0,0,0,81,82,5,0,0,1,82,1,1,0,0,0,83,86,3,4,2,0,84,86,3,18,9,0,85,83,1,
  	0,0,0,85,84,1,0,0,0,86,3,1,0,0,0,87,88,5,1,0,0,88,92,5,38,0,0,89,90,5,
  	2,0,0,90,91,5,3,0,0,91,93,5,38,0,0,92,89,1,0,0,0,92,93,1,0,0,0,93,94,
  	1,0,0,0,94,96,3,6,3,0,95,97,5,4,0,0,96,95,1,0,0,0,96,97,1,0,0,0,97,5,
  	1,0,0,0,98,100,5,5,0,0,99,101,3,8,4,0,100,99,1,0,0,0,100,101,1,0,0,0,
  	101,105,1,0,0,0,102,104,3,10,5,0,103,102,1,0,0,0,104,107,1,0,0,0,105,
  	103,1,0,0,0,105,106,1,0,0,0,106,108,1,0,0,0,107,105,1,0,0,0,108,109,5,
  	6,0,0,109,7,1,0,0,0,110,111,5,3,0,0,111,112,5,2,0,0,112,9,1,0,0,0,113,
  	117,3,12,6,0,114,117,3,16,8,0,115,117,3,14,7,0,116,113,1,0,0,0,116,114,
  	1,0,0,0,116,115,1,0,0,0,117,11,1,0,0,0,118,119,3,70,35,0,119,120,5,38,
  	0,0,120,121,5,4,0,0,121,13,1,0,0,0,122,123,5,38,0,0,123,125,5,7,0,0,124,
  	126,3,20,10,0,125,124,1,0,0,0,125,126,1,0,0,0,126,127,1,0,0,0,127,128,
  	5,8,0,0,128,129,3,32,16,0,129,15,1,0,0,0,130,132,5,9,0,0,131,130,1,0,
  	0,0,131,132,1,0,0,0,132,133,1,0,0,0,133,134,3,70,35,0,134,135,5,38,0,
  	0,135,137,5,7,0,0,136,138,3,20,10,0,137,136,1,0,0,0,137,138,1,0,0,0,138,
  	139,1,0,0,0,139,140,5,8,0,0,140,142,3,32,16,0,141,143,5,4,0,0,142,141,
  	1,0,0,0,142,143,1,0,0,0,143,17,1,0,0,0,144,145,3,70,35,0,145,146,5,38,
  	0,0,146,148,5,7,0,0,147,149,3,20,10,0,148,147,1,0,0,0,148,149,1,0,0,0,
  	149,150,1,0,0,0,150,151,5,8,0,0,151,152,3,32,16,0,152,19,1,0,0,0,153,
  	158,3,22,11,0,154,155,5,10,0,0,155,157,3,22,11,0,156,154,1,0,0,0,157,
  	160,1,0,0,0,158,156,1,0,0,0,158,159,1,0,0,0,159,21,1,0,0,0,160,158,1,
  	0,0,0,161,163,3,70,35,0,162,164,5,40,0,0,163,162,1,0,0,0,163,164,1,0,
  	0,0,164,165,1,0,0,0,165,166,5,38,0,0,166,23,1,0,0,0,167,175,3,26,13,0,
  	168,175,3,28,14,0,169,175,3,30,15,0,170,175,3,32,16,0,171,175,3,34,17,
  	0,172,175,3,36,18,0,173,175,3,38,19,0,174,167,1,0,0,0,174,168,1,0,0,0,
  	174,169,1,0,0,0,174,170,1,0,0,0,174,171,1,0,0,0,174,172,1,0,0,0,174,173,
  	1,0,0,0,175,25,1,0,0,0,176,178,3,70,35,0,177,179,5,40,0,0,178,177,1,0,
  	0,0,178,179,1,0,0,0,179,180,1,0,0,0,180,183,5,38,0,0,181,182,5,11,0,0,
  	182,184,3,40,20,0,183,181,1,0,0,0,183,184,1,0,0,0,184,185,1,0,0,0,185,
  	186,5,4,0,0,186,27,1,0,0,0,187,188,3,58,29,0,188,189,5,11,0,0,189,190,
  	3,40,20,0,190,191,5,4,0,0,191,29,1,0,0,0,192,193,3,40,20,0,193,194,5,
  	4,0,0,194,31,1,0,0,0,195,199,5,5,0,0,196,198,3,24,12,0,197,196,1,0,0,
  	0,198,201,1,0,0,0,199,197,1,0,0,0,199,200,1,0,0,0,200,202,1,0,0,0,201,
  	199,1,0,0,0,202,203,5,6,0,0,203,33,1,0,0,0,204,205,5,12,0,0,205,206,5,
  	7,0,0,206,207,3,40,20,0,207,208,5,8,0,0,208,209,3,24,12,0,209,35,1,0,
  	0,0,210,211,5,13,0,0,211,212,5,7,0,0,212,213,3,40,20,0,213,214,5,8,0,
  	0,214,217,3,24,12,0,215,216,5,14,0,0,216,218,3,24,12,0,217,215,1,0,0,
  	0,217,218,1,0,0,0,218,37,1,0,0,0,219,221,5,15,0,0,220,222,3,40,20,0,221,
  	220,1,0,0,0,221,222,1,0,0,0,222,223,1,0,0,0,223,224,5,4,0,0,224,39,1,
  	0,0,0,225,226,3,42,21,0,226,41,1,0,0,0,227,228,3,44,22,0,228,43,1,0,0,
  	0,229,234,3,46,23,0,230,231,5,16,0,0,231,233,3,46,23,0,232,230,1,0,0,
  	0,233,236,1,0,0,0,234,232,1,0,0,0,234,235,1,0,0,0,235,45,1,0,0,0,236,
  	234,1,0,0,0,237,242,3,48,24,0,238,239,5,17,0,0,239,241,3,48,24,0,240,
  	238,1,0,0,0,241,244,1,0,0,0,242,240,1,0,0,0,242,243,1,0,0,0,243,47,1,
  	0,0,0,244,242,1,0,0,0,245,250,3,50,25,0,246,247,7,0,0,0,247,249,3,50,
  	25,0,248,246,1,0,0,0,249,252,1,0,0,0,250,248,1,0,0,0,250,251,1,0,0,0,
  	251,49,1,0,0,0,252,250,1,0,0,0,253,258,3,52,26,0,254,255,7,1,0,0,255,
  	257,3,52,26,0,256,254,1,0,0,0,257,260,1,0,0,0,258,256,1,0,0,0,258,259,
  	1,0,0,0,259,51,1,0,0,0,260,258,1,0,0,0,261,266,3,54,27,0,262,263,7,2,
  	0,0,263,265,3,54,27,0,264,262,1,0,0,0,265,268,1,0,0,0,266,264,1,0,0,0,
  	266,267,1,0,0,0,267,53,1,0,0,0,268,266,1,0,0,0,269,274,3,56,28,0,270,
  	271,7,3,0,0,271,273,3,56,28,0,272,270,1,0,0,0,273,276,1,0,0,0,274,272,
  	1,0,0,0,274,275,1,0,0,0,275,55,1,0,0,0,276,274,1,0,0,0,277,278,5,29,0,
  	0,278,283,3,56,28,0,279,280,7,2,0,0,280,283,3,56,28,0,281,283,3,58,29,
  	0,282,277,1,0,0,0,282,279,1,0,0,0,282,281,1,0,0,0,283,57,1,0,0,0,284,
  	289,3,66,33,0,285,288,3,60,30,0,286,288,3,62,31,0,287,285,1,0,0,0,287,
  	286,1,0,0,0,288,291,1,0,0,0,289,287,1,0,0,0,289,290,1,0,0,0,290,59,1,
  	0,0,0,291,289,1,0,0,0,292,293,5,30,0,0,293,294,5,38,0,0,294,61,1,0,0,
  	0,295,297,5,7,0,0,296,298,3,64,32,0,297,296,1,0,0,0,297,298,1,0,0,0,298,
  	299,1,0,0,0,299,300,5,8,0,0,300,63,1,0,0,0,301,306,3,40,20,0,302,303,
  	5,10,0,0,303,305,3,40,20,0,304,302,1,0,0,0,305,308,1,0,0,0,306,304,1,
  	0,0,0,306,307,1,0,0,0,307,65,1,0,0,0,308,306,1,0,0,0,309,316,3,68,34,
  	0,310,316,5,38,0,0,311,312,5,7,0,0,312,313,3,40,20,0,313,314,5,8,0,0,
  	314,316,1,0,0,0,315,309,1,0,0,0,315,310,1,0,0,0,315,311,1,0,0,0,316,67,
  	1,0,0,0,317,318,7,4,0,0,318,69,1,0,0,0,319,320,3,72,36,0,320,71,1,0,0,
  	0,321,322,7,5,0,0,322,73,1,0,0,0,33,76,78,85,92,96,100,105,116,125,131,
  	137,142,148,158,163,174,178,183,199,217,221,234,242,250,258,266,274,282,
  	287,289,297,306,315
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  cppParserStaticData = staticData.release();
}

}

cppParser::cppParser(TokenStream *input) : cppParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

cppParser::cppParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  cppParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *cppParserStaticData->atn, cppParserStaticData->decisionToDFA, cppParserStaticData->sharedContextCache, options);
}

cppParser::~cppParser() {
  delete _interpreter;
}

const atn::ATN& cppParser::getATN() const {
  return *cppParserStaticData->atn;
}

std::string cppParser::getGrammarFileName() const {
  return "cpp.g4";
}

const std::vector<std::string>& cppParser::getRuleNames() const {
  return cppParserStaticData->ruleNames;
}

const dfa::Vocabulary& cppParser::getVocabulary() const {
  return cppParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView cppParser::getSerializedATN() const {
  return cppParserStaticData->serializedATN;
}


//----------------- StartContext ------------------------------------------------------------------

cppParser::StartContext::StartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* cppParser::StartContext::EOF() {
  return getToken(cppParser::EOF, 0);
}

std::vector<cppParser::TopLevelDeclContext *> cppParser::StartContext::topLevelDecl() {
  return getRuleContexts<cppParser::TopLevelDeclContext>();
}

cppParser::TopLevelDeclContext* cppParser::StartContext::topLevelDecl(size_t i) {
  return getRuleContext<cppParser::TopLevelDeclContext>(i);
}

std::vector<cppParser::StmtContext *> cppParser::StartContext::stmt() {
  return getRuleContexts<cppParser::StmtContext>();
}

cppParser::StmtContext* cppParser::StartContext::stmt(size_t i) {
  return getRuleContext<cppParser::StmtContext>(i);
}


size_t cppParser::StartContext::getRuleIndex() const {
  return cppParser::RuleStart;
}

void cppParser::StartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStart(this);
}

void cppParser::StartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStart(this);
}

cppParser::StartContext* cppParser::start() {
  StartContext *_localctx = _tracker.createInstance<StartContext>(_ctx, getState());
  enterRule(_localctx, 0, cppParser::RuleStart);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7695021158562) != 0)) {
      setState(76);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(74);
        topLevelDecl();
        break;
      }

      case 2: {
        setState(75);
        stmt();
        break;
      }

      default:
        break;
      }
      setState(80);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(81);
    match(cppParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TopLevelDeclContext ------------------------------------------------------------------

cppParser::TopLevelDeclContext::TopLevelDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::ClassDeclContext* cppParser::TopLevelDeclContext::classDecl() {
  return getRuleContext<cppParser::ClassDeclContext>(0);
}

cppParser::FnDeclContext* cppParser::TopLevelDeclContext::fnDecl() {
  return getRuleContext<cppParser::FnDeclContext>(0);
}


size_t cppParser::TopLevelDeclContext::getRuleIndex() const {
  return cppParser::RuleTopLevelDecl;
}

void cppParser::TopLevelDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTopLevelDecl(this);
}

void cppParser::TopLevelDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTopLevelDecl(this);
}

cppParser::TopLevelDeclContext* cppParser::topLevelDecl() {
  TopLevelDeclContext *_localctx = _tracker.createInstance<TopLevelDeclContext>(_ctx, getState());
  enterRule(_localctx, 2, cppParser::RuleTopLevelDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(85);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case cppParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(83);
        classDecl();
        break;
      }

      case cppParser::T__32:
      case cppParser::T__33:
      case cppParser::T__34:
      case cppParser::T__35:
      case cppParser::T__36:
      case cppParser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(84);
        fnDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDeclContext ------------------------------------------------------------------

cppParser::ClassDeclContext::ClassDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> cppParser::ClassDeclContext::ID() {
  return getTokens(cppParser::ID);
}

tree::TerminalNode* cppParser::ClassDeclContext::ID(size_t i) {
  return getToken(cppParser::ID, i);
}

cppParser::ClassBodyContext* cppParser::ClassDeclContext::classBody() {
  return getRuleContext<cppParser::ClassBodyContext>(0);
}


size_t cppParser::ClassDeclContext::getRuleIndex() const {
  return cppParser::RuleClassDecl;
}

void cppParser::ClassDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassDecl(this);
}

void cppParser::ClassDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassDecl(this);
}

cppParser::ClassDeclContext* cppParser::classDecl() {
  ClassDeclContext *_localctx = _tracker.createInstance<ClassDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, cppParser::RuleClassDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    match(cppParser::T__0);
    setState(88);
    match(cppParser::ID);
    setState(92);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == cppParser::T__1) {
      setState(89);
      match(cppParser::T__1);
      setState(90);
      match(cppParser::T__2);
      setState(91);
      match(cppParser::ID);
    }
    setState(94);
    classBody();
    setState(96);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == cppParser::T__3) {
      setState(95);
      match(cppParser::T__3);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassBodyContext ------------------------------------------------------------------

cppParser::ClassBodyContext::ClassBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::AccessSpecContext* cppParser::ClassBodyContext::accessSpec() {
  return getRuleContext<cppParser::AccessSpecContext>(0);
}

std::vector<cppParser::ClassMemberContext *> cppParser::ClassBodyContext::classMember() {
  return getRuleContexts<cppParser::ClassMemberContext>();
}

cppParser::ClassMemberContext* cppParser::ClassBodyContext::classMember(size_t i) {
  return getRuleContext<cppParser::ClassMemberContext>(i);
}


size_t cppParser::ClassBodyContext::getRuleIndex() const {
  return cppParser::RuleClassBody;
}

void cppParser::ClassBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassBody(this);
}

void cppParser::ClassBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassBody(this);
}

cppParser::ClassBodyContext* cppParser::classBody() {
  ClassBodyContext *_localctx = _tracker.createInstance<ClassBodyContext>(_ctx, getState());
  enterRule(_localctx, 6, cppParser::RuleClassBody);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(98);
    match(cppParser::T__4);
    setState(100);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == cppParser::T__2) {
      setState(99);
      accessSpec();
    }
    setState(105);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 541165879808) != 0)) {
      setState(102);
      classMember();
      setState(107);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(108);
    match(cppParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AccessSpecContext ------------------------------------------------------------------

cppParser::AccessSpecContext::AccessSpecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t cppParser::AccessSpecContext::getRuleIndex() const {
  return cppParser::RuleAccessSpec;
}

void cppParser::AccessSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAccessSpec(this);
}

void cppParser::AccessSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAccessSpec(this);
}

cppParser::AccessSpecContext* cppParser::accessSpec() {
  AccessSpecContext *_localctx = _tracker.createInstance<AccessSpecContext>(_ctx, getState());
  enterRule(_localctx, 8, cppParser::RuleAccessSpec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    match(cppParser::T__2);
    setState(111);
    match(cppParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassMemberContext ------------------------------------------------------------------

cppParser::ClassMemberContext::ClassMemberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::FieldDeclContext* cppParser::ClassMemberContext::fieldDecl() {
  return getRuleContext<cppParser::FieldDeclContext>(0);
}

cppParser::MethodDeclContext* cppParser::ClassMemberContext::methodDecl() {
  return getRuleContext<cppParser::MethodDeclContext>(0);
}

cppParser::CtorDeclContext* cppParser::ClassMemberContext::ctorDecl() {
  return getRuleContext<cppParser::CtorDeclContext>(0);
}


size_t cppParser::ClassMemberContext::getRuleIndex() const {
  return cppParser::RuleClassMember;
}

void cppParser::ClassMemberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassMember(this);
}

void cppParser::ClassMemberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassMember(this);
}

cppParser::ClassMemberContext* cppParser::classMember() {
  ClassMemberContext *_localctx = _tracker.createInstance<ClassMemberContext>(_ctx, getState());
  enterRule(_localctx, 10, cppParser::RuleClassMember);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(116);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(113);
      fieldDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(114);
      methodDecl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(115);
      ctorDecl();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldDeclContext ------------------------------------------------------------------

cppParser::FieldDeclContext::FieldDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::TypeContext* cppParser::FieldDeclContext::type() {
  return getRuleContext<cppParser::TypeContext>(0);
}

tree::TerminalNode* cppParser::FieldDeclContext::ID() {
  return getToken(cppParser::ID, 0);
}


size_t cppParser::FieldDeclContext::getRuleIndex() const {
  return cppParser::RuleFieldDecl;
}

void cppParser::FieldDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFieldDecl(this);
}

void cppParser::FieldDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFieldDecl(this);
}

cppParser::FieldDeclContext* cppParser::fieldDecl() {
  FieldDeclContext *_localctx = _tracker.createInstance<FieldDeclContext>(_ctx, getState());
  enterRule(_localctx, 12, cppParser::RuleFieldDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    type();
    setState(119);
    match(cppParser::ID);
    setState(120);
    match(cppParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CtorDeclContext ------------------------------------------------------------------

cppParser::CtorDeclContext::CtorDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* cppParser::CtorDeclContext::ID() {
  return getToken(cppParser::ID, 0);
}

cppParser::BlockContext* cppParser::CtorDeclContext::block() {
  return getRuleContext<cppParser::BlockContext>(0);
}

cppParser::ParamsContext* cppParser::CtorDeclContext::params() {
  return getRuleContext<cppParser::ParamsContext>(0);
}


size_t cppParser::CtorDeclContext::getRuleIndex() const {
  return cppParser::RuleCtorDecl;
}

void cppParser::CtorDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCtorDecl(this);
}

void cppParser::CtorDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCtorDecl(this);
}

cppParser::CtorDeclContext* cppParser::ctorDecl() {
  CtorDeclContext *_localctx = _tracker.createInstance<CtorDeclContext>(_ctx, getState());
  enterRule(_localctx, 14, cppParser::RuleCtorDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(cppParser::ID);
    setState(123);
    match(cppParser::T__6);
    setState(125);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 541165879296) != 0)) {
      setState(124);
      params();
    }
    setState(127);
    match(cppParser::T__7);
    setState(128);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodDeclContext ------------------------------------------------------------------

cppParser::MethodDeclContext::MethodDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::TypeContext* cppParser::MethodDeclContext::type() {
  return getRuleContext<cppParser::TypeContext>(0);
}

tree::TerminalNode* cppParser::MethodDeclContext::ID() {
  return getToken(cppParser::ID, 0);
}

cppParser::BlockContext* cppParser::MethodDeclContext::block() {
  return getRuleContext<cppParser::BlockContext>(0);
}

cppParser::ParamsContext* cppParser::MethodDeclContext::params() {
  return getRuleContext<cppParser::ParamsContext>(0);
}


size_t cppParser::MethodDeclContext::getRuleIndex() const {
  return cppParser::RuleMethodDecl;
}

void cppParser::MethodDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodDecl(this);
}

void cppParser::MethodDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodDecl(this);
}

cppParser::MethodDeclContext* cppParser::methodDecl() {
  MethodDeclContext *_localctx = _tracker.createInstance<MethodDeclContext>(_ctx, getState());
  enterRule(_localctx, 16, cppParser::RuleMethodDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == cppParser::T__8) {
      setState(130);
      match(cppParser::T__8);
    }
    setState(133);
    type();
    setState(134);
    match(cppParser::ID);
    setState(135);
    match(cppParser::T__6);
    setState(137);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 541165879296) != 0)) {
      setState(136);
      params();
    }
    setState(139);
    match(cppParser::T__7);
    setState(140);
    block();
    setState(142);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == cppParser::T__3) {
      setState(141);
      match(cppParser::T__3);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FnDeclContext ------------------------------------------------------------------

cppParser::FnDeclContext::FnDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::TypeContext* cppParser::FnDeclContext::type() {
  return getRuleContext<cppParser::TypeContext>(0);
}

tree::TerminalNode* cppParser::FnDeclContext::ID() {
  return getToken(cppParser::ID, 0);
}

cppParser::BlockContext* cppParser::FnDeclContext::block() {
  return getRuleContext<cppParser::BlockContext>(0);
}

cppParser::ParamsContext* cppParser::FnDeclContext::params() {
  return getRuleContext<cppParser::ParamsContext>(0);
}


size_t cppParser::FnDeclContext::getRuleIndex() const {
  return cppParser::RuleFnDecl;
}

void cppParser::FnDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnDecl(this);
}

void cppParser::FnDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnDecl(this);
}

cppParser::FnDeclContext* cppParser::fnDecl() {
  FnDeclContext *_localctx = _tracker.createInstance<FnDeclContext>(_ctx, getState());
  enterRule(_localctx, 18, cppParser::RuleFnDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(144);
    type();
    setState(145);
    match(cppParser::ID);
    setState(146);
    match(cppParser::T__6);
    setState(148);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 541165879296) != 0)) {
      setState(147);
      params();
    }
    setState(150);
    match(cppParser::T__7);
    setState(151);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamsContext ------------------------------------------------------------------

cppParser::ParamsContext::ParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<cppParser::ParamContext *> cppParser::ParamsContext::param() {
  return getRuleContexts<cppParser::ParamContext>();
}

cppParser::ParamContext* cppParser::ParamsContext::param(size_t i) {
  return getRuleContext<cppParser::ParamContext>(i);
}


size_t cppParser::ParamsContext::getRuleIndex() const {
  return cppParser::RuleParams;
}

void cppParser::ParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParams(this);
}

void cppParser::ParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParams(this);
}

cppParser::ParamsContext* cppParser::params() {
  ParamsContext *_localctx = _tracker.createInstance<ParamsContext>(_ctx, getState());
  enterRule(_localctx, 20, cppParser::RuleParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    param();
    setState(158);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == cppParser::T__9) {
      setState(154);
      match(cppParser::T__9);
      setState(155);
      param();
      setState(160);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

cppParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::TypeContext* cppParser::ParamContext::type() {
  return getRuleContext<cppParser::TypeContext>(0);
}

tree::TerminalNode* cppParser::ParamContext::ID() {
  return getToken(cppParser::ID, 0);
}

tree::TerminalNode* cppParser::ParamContext::AMP() {
  return getToken(cppParser::AMP, 0);
}


size_t cppParser::ParamContext::getRuleIndex() const {
  return cppParser::RuleParam;
}

void cppParser::ParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam(this);
}

void cppParser::ParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam(this);
}

cppParser::ParamContext* cppParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 22, cppParser::RuleParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    type();
    setState(163);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == cppParser::AMP) {
      setState(162);
      match(cppParser::AMP);
    }
    setState(165);
    match(cppParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

cppParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::VardeclContext* cppParser::StmtContext::vardecl() {
  return getRuleContext<cppParser::VardeclContext>(0);
}

cppParser::AssignContext* cppParser::StmtContext::assign() {
  return getRuleContext<cppParser::AssignContext>(0);
}

cppParser::ExprStmtContext* cppParser::StmtContext::exprStmt() {
  return getRuleContext<cppParser::ExprStmtContext>(0);
}

cppParser::BlockContext* cppParser::StmtContext::block() {
  return getRuleContext<cppParser::BlockContext>(0);
}

cppParser::WhileStmtContext* cppParser::StmtContext::whileStmt() {
  return getRuleContext<cppParser::WhileStmtContext>(0);
}

cppParser::IfStmtContext* cppParser::StmtContext::ifStmt() {
  return getRuleContext<cppParser::IfStmtContext>(0);
}

cppParser::ReturnStmtContext* cppParser::StmtContext::returnStmt() {
  return getRuleContext<cppParser::ReturnStmtContext>(0);
}


size_t cppParser::StmtContext::getRuleIndex() const {
  return cppParser::RuleStmt;
}

void cppParser::StmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt(this);
}

void cppParser::StmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt(this);
}

cppParser::StmtContext* cppParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 24, cppParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(174);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(167);
      vardecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(168);
      assign();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(169);
      exprStmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(170);
      block();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(171);
      whileStmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(172);
      ifStmt();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(173);
      returnStmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardeclContext ------------------------------------------------------------------

cppParser::VardeclContext::VardeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::TypeContext* cppParser::VardeclContext::type() {
  return getRuleContext<cppParser::TypeContext>(0);
}

tree::TerminalNode* cppParser::VardeclContext::ID() {
  return getToken(cppParser::ID, 0);
}

tree::TerminalNode* cppParser::VardeclContext::AMP() {
  return getToken(cppParser::AMP, 0);
}

cppParser::ExprContext* cppParser::VardeclContext::expr() {
  return getRuleContext<cppParser::ExprContext>(0);
}


size_t cppParser::VardeclContext::getRuleIndex() const {
  return cppParser::RuleVardecl;
}

void cppParser::VardeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVardecl(this);
}

void cppParser::VardeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVardecl(this);
}

cppParser::VardeclContext* cppParser::vardecl() {
  VardeclContext *_localctx = _tracker.createInstance<VardeclContext>(_ctx, getState());
  enterRule(_localctx, 26, cppParser::RuleVardecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    type();
    setState(178);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == cppParser::AMP) {
      setState(177);
      match(cppParser::AMP);
    }
    setState(180);
    match(cppParser::ID);
    setState(183);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == cppParser::T__10) {
      setState(181);
      match(cppParser::T__10);
      setState(182);
      expr();
    }
    setState(185);
    match(cppParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignContext ------------------------------------------------------------------

cppParser::AssignContext::AssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::PostfixExprContext* cppParser::AssignContext::postfixExpr() {
  return getRuleContext<cppParser::PostfixExprContext>(0);
}

cppParser::ExprContext* cppParser::AssignContext::expr() {
  return getRuleContext<cppParser::ExprContext>(0);
}


size_t cppParser::AssignContext::getRuleIndex() const {
  return cppParser::RuleAssign;
}

void cppParser::AssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssign(this);
}

void cppParser::AssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssign(this);
}

cppParser::AssignContext* cppParser::assign() {
  AssignContext *_localctx = _tracker.createInstance<AssignContext>(_ctx, getState());
  enterRule(_localctx, 28, cppParser::RuleAssign);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    postfixExpr();
    setState(188);
    match(cppParser::T__10);
    setState(189);
    expr();
    setState(190);
    match(cppParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprStmtContext ------------------------------------------------------------------

cppParser::ExprStmtContext::ExprStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::ExprContext* cppParser::ExprStmtContext::expr() {
  return getRuleContext<cppParser::ExprContext>(0);
}


size_t cppParser::ExprStmtContext::getRuleIndex() const {
  return cppParser::RuleExprStmt;
}

void cppParser::ExprStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprStmt(this);
}

void cppParser::ExprStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprStmt(this);
}

cppParser::ExprStmtContext* cppParser::exprStmt() {
  ExprStmtContext *_localctx = _tracker.createInstance<ExprStmtContext>(_ctx, getState());
  enterRule(_localctx, 30, cppParser::RuleExprStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    expr();
    setState(193);
    match(cppParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

cppParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<cppParser::StmtContext *> cppParser::BlockContext::stmt() {
  return getRuleContexts<cppParser::StmtContext>();
}

cppParser::StmtContext* cppParser::BlockContext::stmt(size_t i) {
  return getRuleContext<cppParser::StmtContext>(i);
}


size_t cppParser::BlockContext::getRuleIndex() const {
  return cppParser::RuleBlock;
}

void cppParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void cppParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}

cppParser::BlockContext* cppParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 32, cppParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    match(cppParser::T__4);
    setState(199);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7695021158560) != 0)) {
      setState(196);
      stmt();
      setState(201);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(202);
    match(cppParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStmtContext ------------------------------------------------------------------

cppParser::WhileStmtContext::WhileStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::ExprContext* cppParser::WhileStmtContext::expr() {
  return getRuleContext<cppParser::ExprContext>(0);
}

cppParser::StmtContext* cppParser::WhileStmtContext::stmt() {
  return getRuleContext<cppParser::StmtContext>(0);
}


size_t cppParser::WhileStmtContext::getRuleIndex() const {
  return cppParser::RuleWhileStmt;
}

void cppParser::WhileStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStmt(this);
}

void cppParser::WhileStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStmt(this);
}

cppParser::WhileStmtContext* cppParser::whileStmt() {
  WhileStmtContext *_localctx = _tracker.createInstance<WhileStmtContext>(_ctx, getState());
  enterRule(_localctx, 34, cppParser::RuleWhileStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(204);
    match(cppParser::T__11);
    setState(205);
    match(cppParser::T__6);
    setState(206);
    expr();
    setState(207);
    match(cppParser::T__7);
    setState(208);
    stmt();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStmtContext ------------------------------------------------------------------

cppParser::IfStmtContext::IfStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::ExprContext* cppParser::IfStmtContext::expr() {
  return getRuleContext<cppParser::ExprContext>(0);
}

std::vector<cppParser::StmtContext *> cppParser::IfStmtContext::stmt() {
  return getRuleContexts<cppParser::StmtContext>();
}

cppParser::StmtContext* cppParser::IfStmtContext::stmt(size_t i) {
  return getRuleContext<cppParser::StmtContext>(i);
}


size_t cppParser::IfStmtContext::getRuleIndex() const {
  return cppParser::RuleIfStmt;
}

void cppParser::IfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStmt(this);
}

void cppParser::IfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStmt(this);
}

cppParser::IfStmtContext* cppParser::ifStmt() {
  IfStmtContext *_localctx = _tracker.createInstance<IfStmtContext>(_ctx, getState());
  enterRule(_localctx, 36, cppParser::RuleIfStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(210);
    match(cppParser::T__12);
    setState(211);
    match(cppParser::T__6);
    setState(212);
    expr();
    setState(213);
    match(cppParser::T__7);
    setState(214);
    stmt();
    setState(217);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(215);
      match(cppParser::T__13);
      setState(216);
      stmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStmtContext ------------------------------------------------------------------

cppParser::ReturnStmtContext::ReturnStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::ExprContext* cppParser::ReturnStmtContext::expr() {
  return getRuleContext<cppParser::ExprContext>(0);
}


size_t cppParser::ReturnStmtContext::getRuleIndex() const {
  return cppParser::RuleReturnStmt;
}

void cppParser::ReturnStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStmt(this);
}

void cppParser::ReturnStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStmt(this);
}

cppParser::ReturnStmtContext* cppParser::returnStmt() {
  ReturnStmtContext *_localctx = _tracker.createInstance<ReturnStmtContext>(_ctx, getState());
  enterRule(_localctx, 38, cppParser::RuleReturnStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    match(cppParser::T__14);
    setState(221);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7428733141120) != 0)) {
      setState(220);
      expr();
    }
    setState(223);
    match(cppParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

cppParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::AssignExprContext* cppParser::ExprContext::assignExpr() {
  return getRuleContext<cppParser::AssignExprContext>(0);
}


size_t cppParser::ExprContext::getRuleIndex() const {
  return cppParser::RuleExpr;
}

void cppParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void cppParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}

cppParser::ExprContext* cppParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 40, cppParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(225);
    assignExpr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignExprContext ------------------------------------------------------------------

cppParser::AssignExprContext::AssignExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::LogicalOrExprContext* cppParser::AssignExprContext::logicalOrExpr() {
  return getRuleContext<cppParser::LogicalOrExprContext>(0);
}


size_t cppParser::AssignExprContext::getRuleIndex() const {
  return cppParser::RuleAssignExpr;
}

void cppParser::AssignExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignExpr(this);
}

void cppParser::AssignExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignExpr(this);
}

cppParser::AssignExprContext* cppParser::assignExpr() {
  AssignExprContext *_localctx = _tracker.createInstance<AssignExprContext>(_ctx, getState());
  enterRule(_localctx, 42, cppParser::RuleAssignExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(227);
    logicalOrExpr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalOrExprContext ------------------------------------------------------------------

cppParser::LogicalOrExprContext::LogicalOrExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<cppParser::LogicalAndExprContext *> cppParser::LogicalOrExprContext::logicalAndExpr() {
  return getRuleContexts<cppParser::LogicalAndExprContext>();
}

cppParser::LogicalAndExprContext* cppParser::LogicalOrExprContext::logicalAndExpr(size_t i) {
  return getRuleContext<cppParser::LogicalAndExprContext>(i);
}


size_t cppParser::LogicalOrExprContext::getRuleIndex() const {
  return cppParser::RuleLogicalOrExpr;
}

void cppParser::LogicalOrExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOrExpr(this);
}

void cppParser::LogicalOrExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOrExpr(this);
}

cppParser::LogicalOrExprContext* cppParser::logicalOrExpr() {
  LogicalOrExprContext *_localctx = _tracker.createInstance<LogicalOrExprContext>(_ctx, getState());
  enterRule(_localctx, 44, cppParser::RuleLogicalOrExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(229);
    logicalAndExpr();
    setState(234);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == cppParser::T__15) {
      setState(230);
      match(cppParser::T__15);
      setState(231);
      logicalAndExpr();
      setState(236);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalAndExprContext ------------------------------------------------------------------

cppParser::LogicalAndExprContext::LogicalAndExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<cppParser::EqualityExprContext *> cppParser::LogicalAndExprContext::equalityExpr() {
  return getRuleContexts<cppParser::EqualityExprContext>();
}

cppParser::EqualityExprContext* cppParser::LogicalAndExprContext::equalityExpr(size_t i) {
  return getRuleContext<cppParser::EqualityExprContext>(i);
}


size_t cppParser::LogicalAndExprContext::getRuleIndex() const {
  return cppParser::RuleLogicalAndExpr;
}

void cppParser::LogicalAndExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalAndExpr(this);
}

void cppParser::LogicalAndExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalAndExpr(this);
}

cppParser::LogicalAndExprContext* cppParser::logicalAndExpr() {
  LogicalAndExprContext *_localctx = _tracker.createInstance<LogicalAndExprContext>(_ctx, getState());
  enterRule(_localctx, 46, cppParser::RuleLogicalAndExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(237);
    equalityExpr();
    setState(242);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == cppParser::T__16) {
      setState(238);
      match(cppParser::T__16);
      setState(239);
      equalityExpr();
      setState(244);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExprContext ------------------------------------------------------------------

cppParser::EqualityExprContext::EqualityExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<cppParser::RelationalExprContext *> cppParser::EqualityExprContext::relationalExpr() {
  return getRuleContexts<cppParser::RelationalExprContext>();
}

cppParser::RelationalExprContext* cppParser::EqualityExprContext::relationalExpr(size_t i) {
  return getRuleContext<cppParser::RelationalExprContext>(i);
}


size_t cppParser::EqualityExprContext::getRuleIndex() const {
  return cppParser::RuleEqualityExpr;
}

void cppParser::EqualityExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpr(this);
}

void cppParser::EqualityExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpr(this);
}

cppParser::EqualityExprContext* cppParser::equalityExpr() {
  EqualityExprContext *_localctx = _tracker.createInstance<EqualityExprContext>(_ctx, getState());
  enterRule(_localctx, 48, cppParser::RuleEqualityExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(245);
    relationalExpr();
    setState(250);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == cppParser::T__17

    || _la == cppParser::T__18) {
      setState(246);
      _la = _input->LA(1);
      if (!(_la == cppParser::T__17

      || _la == cppParser::T__18)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(247);
      relationalExpr();
      setState(252);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExprContext ------------------------------------------------------------------

cppParser::RelationalExprContext::RelationalExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<cppParser::AdditiveExprContext *> cppParser::RelationalExprContext::additiveExpr() {
  return getRuleContexts<cppParser::AdditiveExprContext>();
}

cppParser::AdditiveExprContext* cppParser::RelationalExprContext::additiveExpr(size_t i) {
  return getRuleContext<cppParser::AdditiveExprContext>(i);
}


size_t cppParser::RelationalExprContext::getRuleIndex() const {
  return cppParser::RuleRelationalExpr;
}

void cppParser::RelationalExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpr(this);
}

void cppParser::RelationalExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpr(this);
}

cppParser::RelationalExprContext* cppParser::relationalExpr() {
  RelationalExprContext *_localctx = _tracker.createInstance<RelationalExprContext>(_ctx, getState());
  enterRule(_localctx, 50, cppParser::RuleRelationalExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(253);
    additiveExpr();
    setState(258);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 15728640) != 0)) {
      setState(254);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 15728640) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(255);
      additiveExpr();
      setState(260);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExprContext ------------------------------------------------------------------

cppParser::AdditiveExprContext::AdditiveExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<cppParser::MultiplicativeExprContext *> cppParser::AdditiveExprContext::multiplicativeExpr() {
  return getRuleContexts<cppParser::MultiplicativeExprContext>();
}

cppParser::MultiplicativeExprContext* cppParser::AdditiveExprContext::multiplicativeExpr(size_t i) {
  return getRuleContext<cppParser::MultiplicativeExprContext>(i);
}


size_t cppParser::AdditiveExprContext::getRuleIndex() const {
  return cppParser::RuleAdditiveExpr;
}

void cppParser::AdditiveExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpr(this);
}

void cppParser::AdditiveExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpr(this);
}

cppParser::AdditiveExprContext* cppParser::additiveExpr() {
  AdditiveExprContext *_localctx = _tracker.createInstance<AdditiveExprContext>(_ctx, getState());
  enterRule(_localctx, 52, cppParser::RuleAdditiveExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(261);
    multiplicativeExpr();
    setState(266);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == cppParser::T__23

    || _la == cppParser::T__24) {
      setState(262);
      _la = _input->LA(1);
      if (!(_la == cppParser::T__23

      || _la == cppParser::T__24)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(263);
      multiplicativeExpr();
      setState(268);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExprContext ------------------------------------------------------------------

cppParser::MultiplicativeExprContext::MultiplicativeExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<cppParser::UnaryExprContext *> cppParser::MultiplicativeExprContext::unaryExpr() {
  return getRuleContexts<cppParser::UnaryExprContext>();
}

cppParser::UnaryExprContext* cppParser::MultiplicativeExprContext::unaryExpr(size_t i) {
  return getRuleContext<cppParser::UnaryExprContext>(i);
}


size_t cppParser::MultiplicativeExprContext::getRuleIndex() const {
  return cppParser::RuleMultiplicativeExpr;
}

void cppParser::MultiplicativeExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpr(this);
}

void cppParser::MultiplicativeExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpr(this);
}

cppParser::MultiplicativeExprContext* cppParser::multiplicativeExpr() {
  MultiplicativeExprContext *_localctx = _tracker.createInstance<MultiplicativeExprContext>(_ctx, getState());
  enterRule(_localctx, 54, cppParser::RuleMultiplicativeExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(269);
    unaryExpr();
    setState(274);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 469762048) != 0)) {
      setState(270);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 469762048) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(271);
      unaryExpr();
      setState(276);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExprContext ------------------------------------------------------------------

cppParser::UnaryExprContext::UnaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::UnaryExprContext* cppParser::UnaryExprContext::unaryExpr() {
  return getRuleContext<cppParser::UnaryExprContext>(0);
}

cppParser::PostfixExprContext* cppParser::UnaryExprContext::postfixExpr() {
  return getRuleContext<cppParser::PostfixExprContext>(0);
}


size_t cppParser::UnaryExprContext::getRuleIndex() const {
  return cppParser::RuleUnaryExpr;
}

void cppParser::UnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpr(this);
}

void cppParser::UnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpr(this);
}

cppParser::UnaryExprContext* cppParser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 56, cppParser::RuleUnaryExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(282);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case cppParser::T__28: {
        enterOuterAlt(_localctx, 1);
        setState(277);
        match(cppParser::T__28);
        setState(278);
        unaryExpr();
        break;
      }

      case cppParser::T__23:
      case cppParser::T__24: {
        enterOuterAlt(_localctx, 2);
        setState(279);
        _la = _input->LA(1);
        if (!(_la == cppParser::T__23

        || _la == cppParser::T__24)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(280);
        unaryExpr();
        break;
      }

      case cppParser::T__6:
      case cppParser::T__30:
      case cppParser::T__31:
      case cppParser::ID:
      case cppParser::NUMBER:
      case cppParser::CHAR:
      case cppParser::STRING: {
        enterOuterAlt(_localctx, 3);
        setState(281);
        postfixExpr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PostfixExprContext ------------------------------------------------------------------

cppParser::PostfixExprContext::PostfixExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::PrimaryExprContext* cppParser::PostfixExprContext::primaryExpr() {
  return getRuleContext<cppParser::PrimaryExprContext>(0);
}

std::vector<cppParser::MemberAccessContext *> cppParser::PostfixExprContext::memberAccess() {
  return getRuleContexts<cppParser::MemberAccessContext>();
}

cppParser::MemberAccessContext* cppParser::PostfixExprContext::memberAccess(size_t i) {
  return getRuleContext<cppParser::MemberAccessContext>(i);
}

std::vector<cppParser::CallContext *> cppParser::PostfixExprContext::call() {
  return getRuleContexts<cppParser::CallContext>();
}

cppParser::CallContext* cppParser::PostfixExprContext::call(size_t i) {
  return getRuleContext<cppParser::CallContext>(i);
}


size_t cppParser::PostfixExprContext::getRuleIndex() const {
  return cppParser::RulePostfixExpr;
}

void cppParser::PostfixExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPostfixExpr(this);
}

void cppParser::PostfixExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPostfixExpr(this);
}

cppParser::PostfixExprContext* cppParser::postfixExpr() {
  PostfixExprContext *_localctx = _tracker.createInstance<PostfixExprContext>(_ctx, getState());
  enterRule(_localctx, 58, cppParser::RulePostfixExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(284);
    primaryExpr();
    setState(289);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == cppParser::T__6

    || _la == cppParser::T__29) {
      setState(287);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case cppParser::T__29: {
          setState(285);
          memberAccess();
          break;
        }

        case cppParser::T__6: {
          setState(286);
          call();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(291);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MemberAccessContext ------------------------------------------------------------------

cppParser::MemberAccessContext::MemberAccessContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* cppParser::MemberAccessContext::ID() {
  return getToken(cppParser::ID, 0);
}


size_t cppParser::MemberAccessContext::getRuleIndex() const {
  return cppParser::RuleMemberAccess;
}

void cppParser::MemberAccessContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMemberAccess(this);
}

void cppParser::MemberAccessContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMemberAccess(this);
}

cppParser::MemberAccessContext* cppParser::memberAccess() {
  MemberAccessContext *_localctx = _tracker.createInstance<MemberAccessContext>(_ctx, getState());
  enterRule(_localctx, 60, cppParser::RuleMemberAccess);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(292);
    match(cppParser::T__29);
    setState(293);
    match(cppParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallContext ------------------------------------------------------------------

cppParser::CallContext::CallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::ArgsContext* cppParser::CallContext::args() {
  return getRuleContext<cppParser::ArgsContext>(0);
}


size_t cppParser::CallContext::getRuleIndex() const {
  return cppParser::RuleCall;
}

void cppParser::CallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCall(this);
}

void cppParser::CallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCall(this);
}

cppParser::CallContext* cppParser::call() {
  CallContext *_localctx = _tracker.createInstance<CallContext>(_ctx, getState());
  enterRule(_localctx, 62, cppParser::RuleCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    match(cppParser::T__6);
    setState(297);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7428733141120) != 0)) {
      setState(296);
      args();
    }
    setState(299);
    match(cppParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgsContext ------------------------------------------------------------------

cppParser::ArgsContext::ArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<cppParser::ExprContext *> cppParser::ArgsContext::expr() {
  return getRuleContexts<cppParser::ExprContext>();
}

cppParser::ExprContext* cppParser::ArgsContext::expr(size_t i) {
  return getRuleContext<cppParser::ExprContext>(i);
}


size_t cppParser::ArgsContext::getRuleIndex() const {
  return cppParser::RuleArgs;
}

void cppParser::ArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgs(this);
}

void cppParser::ArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgs(this);
}

cppParser::ArgsContext* cppParser::args() {
  ArgsContext *_localctx = _tracker.createInstance<ArgsContext>(_ctx, getState());
  enterRule(_localctx, 64, cppParser::RuleArgs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(301);
    expr();
    setState(306);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == cppParser::T__9) {
      setState(302);
      match(cppParser::T__9);
      setState(303);
      expr();
      setState(308);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExprContext ------------------------------------------------------------------

cppParser::PrimaryExprContext::PrimaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::LiteralContext* cppParser::PrimaryExprContext::literal() {
  return getRuleContext<cppParser::LiteralContext>(0);
}

tree::TerminalNode* cppParser::PrimaryExprContext::ID() {
  return getToken(cppParser::ID, 0);
}

cppParser::ExprContext* cppParser::PrimaryExprContext::expr() {
  return getRuleContext<cppParser::ExprContext>(0);
}


size_t cppParser::PrimaryExprContext::getRuleIndex() const {
  return cppParser::RulePrimaryExpr;
}

void cppParser::PrimaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpr(this);
}

void cppParser::PrimaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpr(this);
}

cppParser::PrimaryExprContext* cppParser::primaryExpr() {
  PrimaryExprContext *_localctx = _tracker.createInstance<PrimaryExprContext>(_ctx, getState());
  enterRule(_localctx, 66, cppParser::RulePrimaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(315);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case cppParser::T__30:
      case cppParser::T__31:
      case cppParser::NUMBER:
      case cppParser::CHAR:
      case cppParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(309);
        literal();
        break;
      }

      case cppParser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(310);
        match(cppParser::ID);
        break;
      }

      case cppParser::T__6: {
        enterOuterAlt(_localctx, 3);
        setState(311);
        match(cppParser::T__6);
        setState(312);
        expr();
        setState(313);
        match(cppParser::T__7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

cppParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* cppParser::LiteralContext::NUMBER() {
  return getToken(cppParser::NUMBER, 0);
}

tree::TerminalNode* cppParser::LiteralContext::STRING() {
  return getToken(cppParser::STRING, 0);
}

tree::TerminalNode* cppParser::LiteralContext::CHAR() {
  return getToken(cppParser::CHAR, 0);
}


size_t cppParser::LiteralContext::getRuleIndex() const {
  return cppParser::RuleLiteral;
}

void cppParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void cppParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}

cppParser::LiteralContext* cppParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 68, cppParser::RuleLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(317);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7153268031488) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

cppParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

cppParser::BaseTypeContext* cppParser::TypeContext::baseType() {
  return getRuleContext<cppParser::BaseTypeContext>(0);
}


size_t cppParser::TypeContext::getRuleIndex() const {
  return cppParser::RuleType;
}

void cppParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void cppParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}

cppParser::TypeContext* cppParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 70, cppParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(319);
    baseType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BaseTypeContext ------------------------------------------------------------------

cppParser::BaseTypeContext::BaseTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* cppParser::BaseTypeContext::ID() {
  return getToken(cppParser::ID, 0);
}


size_t cppParser::BaseTypeContext::getRuleIndex() const {
  return cppParser::RuleBaseType;
}

void cppParser::BaseTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBaseType(this);
}

void cppParser::BaseTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<cppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBaseType(this);
}

cppParser::BaseTypeContext* cppParser::baseType() {
  BaseTypeContext *_localctx = _tracker.createInstance<BaseTypeContext>(_ctx, getState());
  enterRule(_localctx, 72, cppParser::RuleBaseType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(321);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 541165879296) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void cppParser::initialize() {
  ::antlr4::internal::call_once(cppParserOnceFlag, cppParserInitialize);
}
