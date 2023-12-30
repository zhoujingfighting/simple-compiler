#ifndef __PARSER_H_
#define __PARSER_H_

#include "lexer.h"
#include <cassert>
#include <llvm/Support/ErrorHandling.h>
#include <llvm/Support/raw_ostream.h>
namespace toy {
class Parser {
private:
  Lexer &lexer;

public:
  Parser(Lexer &lexer) : lexer(lexer) {
    llvm::errs() << "Initializing lexer\n";
  }
  Parser(Lexer &lexer, std::string input) : lexer(lexer) {
    llvm::errs() << "Initializing lexer\n";
  }

  virtual ~Parser() = default;

  // Enter parsing point for whole file
  // module :== Functions* | Variables*
  int parseModule() {
    // Get first token
    auto tok = lexer.getNextToken();
    while (lexer.getCurToken() != tok_eof) {
      switch (tok) {
      case tok_var:
      case tok_def:
        lexer.consume(lexer.getCurToken());
        break;
      case tok_semicolon:
      case tok_parenthese_open:
      case tok_parenthese_close:
      case tok_bracket_open:
      case tok_bracket_close:
      case tok_sbracket_open:
      case tok_sbracket_close:
      case tok_eof:
      case tok_return:
      case tok_identifier:
      case tok_number:
        llvm_unreachable("Not expedcted token !");
        break;
      }
    }
    assert(lexer.getCurToken() == tok_eof && "Unexpected end");
    return 0;
  }

  // parse function
  // Functions :== Blocks
};

} // namespace toy
#endif
