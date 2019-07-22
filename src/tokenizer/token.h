struct Token {
    char * value;
    char * the_rest_of_text;
};

struct Token * next_token(const char * text);
