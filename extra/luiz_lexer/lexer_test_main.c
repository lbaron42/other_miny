#include"../../inc/minishell.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./lexer \"input_string\"\n");
        return 1;
    }

    char* input = argv[1];
    int index = 0;

    t_token token;
    while ((token = getnexttoken(input, &index)).type != -1) {
        switch (token.type) {
            case TOKEN_COMMAND:
                printf("Command: %s\n", token.value);
                break;
            case TOKEN_ARGUMENT:
                printf("Argument: %s\n", token.value);
                break;
            case TOKEN_FLAG:
                printf("Flag: %s\n", token.value);
                break;
            case TOKEN_PIPE:
                printf("Pipe\n");
                break;
            case TOKEN_REDIRECTION_IN:
                printf("Redirection In\n");
                break;
            case TOKEN_REDIRECTION_OUT:
                printf("Redirection Out\n");
                break;
            case TOKEN_SPACE:
                printf("Space\n");
                break;
			case  TOKEN_HERE_DOC:
				printf("Here Doc\n");
				break;
			case  TOKEN_APPEND_DOC:
				printf("Append Doc\n");
				break;
				
        }
        index++;
    }

    return 0;
}
