#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>

Parser::Parser(istream* in) {
   scan = new Scanner(in);
}

Parser::~Parser() {
   try {
      delete scan;
   } catch (...) {}
}

AST* Parser::parse() {
   return Prog();
}

AST* Parser::Prog() {
   AST* result = Expr();
   Token* t = scan->getToken();
   if (t->getType() != eof) {
      cout << "Syntax Error: Expected EOF, found token at column " << t->getCol() << endl;
      throw ParseError;
   }

   return result;
}

AST* Parser::Expr() {
   return RestExpr(Term());
}

AST* Parser::RestExpr(AST* e) {
   Token* t = scan->getToken();

   if (t->getType() == add) {
      return RestExpr(new AddNode(e,Term()));
   }

   if (t->getType() == sub)
      return RestExpr(new SubNode(e,Term()));

   scan->putBackToken();

   return e;
}

AST* Parser::Term() {
   return RestTerm(Storable());
}

AST* Parser::RestTerm(AST* e) {
   Token* t = scan->getToken();

   if (t->getType() == times) {
      return RestTerm(new TimesNode(e,Term()));
   }

   if (t->getType() == divide)
      return RestTerm(new DivideNode(e,Term()));

   scan->putBackToken();

   return e; 
}

AST* Parser::Storable() {
   AST* f = Factor();
   Token* t = scan->getToken();
   if(t->getType() == keyword && t->getLex() == "S"){
      //store node
      AST* memL = Factor();
      return new StoreNode(f, memL->evaluate());
   }
   scan->putBackToken();
   return f; 
}

AST* Parser::Factor() {
   Token* t = scan->getToken();
   if (t->getType() == number) {
      istringstream in(t->getLex());
      int val;
      in >> val;

      return new NumNode(val);
   }
   else if(t->getLex() == "R"){
      AST* memL = Factor();
      return new RecallNode(memL->evaluate());
   }
   else if(t->getType() == lparen){
      AST* ex = Expr();

      t = scan->getToken();
      if(t->getType() != rparen){
         cout << "Right parentheses missing" << endl;
      }
      return ex;
   }
   cout << "Factor not implemented" << endl;
   throw ParseError;
}
   
