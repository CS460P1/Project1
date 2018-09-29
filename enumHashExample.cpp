#include <sstream>
#include <iostream> 
#include <unordered_map>


using namespace std;

/*
struct EnumClassHash{
	template <typename T>
	std::size_t operator()(T t) const
	{
		return static_cast<std::size_t>(t);
	}
};
*/



int main(){
	enum token_type {
		NONE = -1, 

		NUMLIT_T,
		IDENT_T,
		STRLIT_T,

		// Key words
		LISTOP_T,
		IF_T,
		CONS_T,
		COND_T,
		ELSE_T,
		DISPLAY_T,
		NEWLINE_T,
		AND_T,
		OR_T,
		NOT_T,
		DEFINE_T,

		// Predicates
		NUMBERP_T,
		LISTP_T,
		ZEROP_T,
		NULLP_T,
		STRINGP_T,


		// Arithmetic
		PLUS_T,
		MINUS_T,
		DIV_T,
		MULT_T,
		MODULO_T,
		ROUND_T,

		// Logical/Relational
		EQUALTO_T,
		GT_T,
		LT_T,
		GTE_T,
		LTE_T,

		// Other
		LPAREN_T,
		RPAREN_T,
		SQUOTE_T,
		ERROR_T,
		EOF_T, 
	};

	int test = NUMLIT_T;	
	cout << test << endl;
	
	/*
	std::unordered_map<string, token_type> myMap;
	//std::unordered_map<token_type, string> myMap;
	myMap["cons"] = CONS_T;

	string key = "brandon";
	
	if(myMap.find(key) == myMap.end())
	{
		cout << key << " not found" << endl;
	}
	else	
		cout << "Found " << key <<endl;

	   string line = "\"this is a string\"";
	   string lexeme;
	   cout << line << endl;
	   istringstream iss(line);
	   while(iss>> lexeme)
	   cout << lexeme << endl;
	 */


	return 0;
}
