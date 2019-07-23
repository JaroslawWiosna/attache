typedef struct Token Token;

struct Token {
    char * value ;
    char * the_rest_of_text;
    Token * prev;
    Token * next;
};

Token * next_token(Token * token);
Token * prev_token(Token * token);
Token * create_next_token(Token * token);
Token * create_token_list(const char * text);

void dctor_token_list(Token * token);
void dctor_token(Token * token);