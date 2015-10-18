#! /usr/bin/python2

from nltk.tokenize import WhitespaceTokenizer
from nltk.tokenize import RegexpTokenizer
from nltk.stem.porter import *
from nltk.corpus import stopwords
import os
import sys

"""Steps to Do:
1- To read a whole file into a variable

2- To obtain letters lowercase from uppercase

3- To remove single quote in terms and to obtain 1 pronoun and 1 verb.
For that, we use <string>.replace() method. Example: i'll => i will

4- Position (Offset) of words is important in this task. Instead of enumerating
all words from 0 to n, we take account the position of first character of words.
Example: "I like shakespeare!"
"I" -> (0,1) [start position, end position]         "I" -> 0
"like" -> (2,6)                             ===>    "like" -> 2
"shakespeare" -> (7,18)                             "shakespeare" -> 7

We can easily obtain this (start, end) information with WhitespaceTokenizer().span_tokenize()
But our goal is also to remove stopwords (of, is, that ...) and to stem. We do these in
the same foor loop. Because every iteration we obtain a raw term data and do preprocesing
for each iteration.

5- In the for loop, we replace '.' by '' because it is a problem for abbreviation: U.S.A.
And then, we use regexp to choose words (and not numbers, date).
So if any term begins by  '"' or lowercase letter, it is OK for us. We should take account
also these at the end of terms: "!", ";", ",", "." ...

6- And then, we remove punctuations in the terms by using toker.tokenize().
Example: "o'clock" -> "oclock", "yes!" -> "yes" ...

7- To stem terms if they are not stopwords (this, is, will ...).
Example: "editor" -> "edit", "edition" -> "edit" ...

8-First, we check if term is interessting to us. We do not want these: "<DOC>", 123, $34, ...
Then, to place terms in key, to place values (position of first character) in values of
dictionary structure.
Example:
"edit" : [12, 45, 89]
"home" : [78]
...

We can easily obtain frequency of terms by len() function: len(vocabs["edit"])
"""

def main():
    regexp=re.compile('^["a-z]+[a-z0-9.?,;"!\')(]*$')
    toker = RegexpTokenizer(r'((?<=[^\w\s])\w(?=[^\w\s])|(\W))+', gaps=True)
    stemmer = PorterStemmer()
    stop = stopwords.words('english')

    # we determine the terms that we'll meet some problem
    terms_to_remove = ["i'll", "you'll", "he'll",
            "she'll", "it'll", "we'll",
            "they'll", "i'm", "you're",
            "he's", "she's", "we're",
            "they're", "i'd", "you'd",
            "he'd", "we'd", "they'd",
            "that's","it's", "how's",
            "what's", "where's", "who's",
            "i've", "you've", "we've",
            "they've", "won't", "didn't",
            "wasn't", "doesn't","don't",
            "couldn't", "can't", "aren't",
            "isn't", "musn't", "let's",
            "hadn't", "haven't", "hasn't",
            "there's", "there're"]


    path_dir = sys.argv[1]
    # check if path_dir is a directory (either local path or global path)
    if not(os.path.isdir(path_dir)) and not(
            os.path.isdir(os.path.join(os.getcwd(),path_dir))):
        return 0
    counter=0
    for filename in sorted(os.listdir(path_dir)):
        counter=counter+1
        vocabs = {}
        with open (path_dir+"/"+filename, "r") as f:
            data=f.read().lower()

        for t in terms_to_remove: # for removing single quote in words
            data = data.replace(t, "!"*len(t)) # like "i'm" => "i am". These are kind of stopwords

        for start, end in WhitespaceTokenizer().span_tokenize(data):
            length = end - start
            term = str(buffer(data, start, length)) # We do not use data[start:end]
                                                    #because, it uses memory each time
            term = term.replace('.', '!') # we do this because of abbreviation like U.S.

            if regexp.search(term): # we get terms intersting to us (not numbers, date ..)
                term = "".join(toker.tokenize(term)) # we remove punctuations
                if term not in stop and len(term)>2: # before tokenizer, term would be '"!!!!!' so output would be ""
                    term = str(stemmer.stem(term)) # output of stemmer.stem(term) is u'string
                    if term not in vocabs:
                        vocabs[term]=[]
                    vocabs[term].append(str(start)) # we add positon information at the end of list

        # we're sending to c++ program in this form: (term name, doc_id, filename, term frequency in doc_id)
        # For now, we dont care about term offsets in the doc_id
        # c++ program catch this infos by doing "std::cin"
        for term, pos in vocabs.iteritems():
            output=' '.join([term, str(counter), filename, str(len(pos))])
            print(output)


main()
