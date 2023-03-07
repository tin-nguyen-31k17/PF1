// Implement void process(const char *str, char *outstr) function which eliminates redundant space characters so that there are no consecutive space characters and there is no space character at the beginning/end of string.
// - Input:
// Char * pointer to the first character of string
// - Output:
// The result is written to outstr
// - Available library: <iostream>, <cstring>
// - Note: Your code MUST NOT contain any of the words in the list {"include", "string"} even in the comment

void process(const char *str, char *outstr)
{
    int i = 0, j = 0;
    int length = strlen(str);

    //Skip leading spaces
    while (i < length && str[i] != ' ') i++;

    //Transfer to outstr & remove redundant spaces
    while (i < length){
        if (str[i] != ' '){
            outstr[j++] = str[i++];
        }
        else{
            outstr[j++] = str[i++];
            while (i < length && str[i] == ' ') i++;
        }
    }

    //Delete trailing spaces
    while (j > 0 && outstr[j - 1] == ' ') j--;
    
    outstr[j] = '\0';
}

// Implement void process(const char *str, char *outstr) function which reverses the string.
// - Input:
// Char * pointer to the first character of string
// - Output:
// The result is written to outstr
// - Available library: <iostream>, <cstring>
// - Note: Your code MUST NOT contain any of the words in the list {"include", "string"} even in the comment

void process(const char *str, char *outstr) {
    int length = strlen(str);
    int i, j;

    for (i = length - 1, j = 0; i >= 0; i--, j++) {
        outstr[j] = str[i];
    }
    outstr[j] = '\0';
}

// Implement int calc(const char *str) function which returns the decimal value of binary string str.
// - Input:
// Char * pointer to the first character of string
// - Output:
// The decimal value of binary string
// - Available library: <iostream>, <cstring>
// - Note: Your code MUST NOT contain any of the words in the list {"include", "string"} even in the comment

int calc(char str[]) {
    int length = strlen(str);
    int i, result = 0;

    for (i = 0; i < length; i++) {
        if (str[i] == '1') {
            result = result * 2 + 1;
        } else if (str[i] == '0') {
            result = result * 2;
        } else {
            return -1;
        }
    }
    return result;
}