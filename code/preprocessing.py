#! /usr/bin/python2

from nltk.tokenize import WhitespaceTokenizer
from nltk.tokenize import RegexpTokenizer
from nltk.stem.porter import *
from nltk.corpus import stopwords

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

regexp=re.compile('^["A-Za-z]+[A-Za-z0-9.?,;"!\']*$')
toker = RegexpTokenizer(r'((?<=[^\w\s])\w(?=[^\w\s])|(\W))+', gaps=True)
stemmer = PorterStemmer()
stop = stopwords.words('english')

# we determine the terms that we'll meet some problem
terms_to_remove = {"i'll": "i will", "you'll": "you will", "he'll":"he will",
        "she'll": "she will", "we'll":"we will", "they'll":"they will",
        "i'm":"i am", "you're":"you are", "he's":"he is", "she's":"she is",
        "we're":"we are", "they're":"they are", "i'd":"i would",
        "you'd":"you would", "he'd":"he would", "we'd":"we would",
        "they'd":"they would", "that's":"that is", "it's":"it is"}

filename = "../db/test1"
with open (filename, "r") as f:
    data_lines=f.readlines()
# Remove '\n' using strip
data = ' '.join(map(str.strip, data_lines))
data = data.lower()

# Filtering terms to remove
data = ' '.join(map(lambda x:terms_to_remove[x] if x in terms_to_remove else x,
                data.split()))

vocabs = {}
for start, end in WhitespaceTokenizer().span_tokenize(data):
    length = end - start
    term = str(buffer(data, start, length)) # We do not use data[start:end] because\
                                            # it use memory each time
    term = term.replace('.', '') # abbreviation'lar icin -> sikinti yaratiyor
    print term

    if regexp.search(term): # we get terms intersting to us (not numbers, date ..)
        term = "".join(toker.tokenize(term)) # we remove punctuations
        if term not in stop:
            term = str(stemmer.stem(term)) # output of stemmer.stem(term) is u'string
            print "==>", term
            if term not in vocabs:
                vocabs[term]=[]
            vocabs[term].append(str(start)) # we add positon information at the end of list

print vocabs
