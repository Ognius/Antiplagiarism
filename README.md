## Antiplagiarism
### Description:
- A web application that performs intelligent text processing functions: Antiplagiarism, etc.

<b>Web-Antiplagiarism</b> is a program that compares the original text with a test fragment (a fragment of text entered by the user). The basis is taken such a system for determining plagiarism: 

- first, we select <code>1, 2, 3</code> words from a fragment of the text, the entered by user, and check if there is such a sequence of words in the original text;
- then select <code>2, 3, 4</code> words and again look for them in the text and etc.;
- after a complete analysis of the text we will calculate the percentage of matching selections and draw a conclusion about the uniqueness of the text.


```c++
#define SELECTION_WORDS 3
// sets the meaning of words in the selection;
// the value can be a positive integer no less than 2 (otherwise the selection is meaningless);
// default value is 3;
//into variables;
```

```c++
string documentText;
string userText;
// formatted original text and user text are transmitted, respectively;
```
<hr>
Text formatting (removing punctuation marks and converting text to lowercase) performs the function:

```c++
void setNormalizeText(char* text);;
```


Final functions of the program, which allow to determine the uniqueness of the text. Selections are counted, and using the proportion method, the function calculates the percentage of plagiarism.

<hr>

<b>The project was made by:</b>

<b>`Alexander Rusak`</b> and <b>`Vital Ahinski`</b>
