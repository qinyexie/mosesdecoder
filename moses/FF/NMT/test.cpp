#include "NMT_Wrapper.h"
#include<iostream>
#include <string>
#include <boost/python.hpp>

using namespace std;
using namespace boost::python;

int main(int argc, char *argv[])
{
    string state_path = string(argv[1]);
    string model_path = string(argv[2]);
    string wrapper_path = string(argv[3]);

    NMT_Wrapper* wrapper = new NMT_Wrapper();
    bool res = wrapper->Init(state_path, model_path, wrapper_path);
    if (res == false) {
        cout << "No wrapper" << endl;
        return 1;
    }

    double prob;
    PyObject* next_state = NULL;
    PyObject* current_state = NULL;

    string source_sentence;
    string next_word;
    string last_word = "";
    cout << "Input sentence:";
    getline(cin, source_sentence);
    PyObject* py_context_vectors;
    wrapper->GetContextVectors(source_sentence, py_context_vectors);
    while (1) {
        if (source_sentence.size() < 3) return 0;

        while (true) {
            cout << "Next word: ";
            getline(cin, next_word);
            bool res = wrapper->GetProb(next_word, py_context_vectors, last_word,
                                        current_state, prob, next_state);
            if (res == false) { cout << "gone wrong.\n"; }
            cout << "Word: " << next_word << "; Prob: " << prob << endl;
            cout << next_state << endl;
            current_state = next_state;
            last_word = next_word;
            if (next_word.size() < 1 ) {
                current_state = NULL;
                next_state = NULL;
                last_word = "";
                cout << "Input sentence:";
                getline(cin, source_sentence);
                wrapper->GetContextVectors(source_sentence, py_context_vectors);
                break;
            }
        }
    }

    return 0;
}
