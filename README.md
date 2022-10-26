# SARC
A fork of [NLPrinceton / SARC](https://github.com/NLPrinceton/SARC).

## Project Setup
1. [Download the dataset.](https://nlp.cs.princeton.edu/SARC/2.0/). Create a folder named `dataset` that is structured like this (don't forget to extract the files):
   ``` 
   dataset/
   ├─ main/
   |   ├─ comments.json
   |   ├─ test-balanced.csv
   |   └─ train-balanced.csv
   └─ pol/
      ├─ comments.json
      ├─ test-balanced.csv
      └─ train-balanced.csv
   ``` 
2. Put the `dataset` folder at this repo's root directory.
3. Still at the repo's root directory, run `git submodule update --init`. This is one of the dependencies to create bag-of-n-grams (bong).
4. If you want to use word embedding instead of bong, download [1600-dimensional Amazon GloVe embeddings](http://nlp.cs.princeton.edu/DisC/amazon_glove1600.txt.bz2) (NOTE: 2.6 GB compressed, 8.7 GB uncompressed). Then put the extracted .txt file inside the `dataset` folder.

## Run the baseline models
Run one of the following commands: (<tt>$EMBEDDING</tt> is the file of downloaded GloVe embeddings)

**'all' dataset**
```bash
# Bag-of-Words on all:
python eval.py main -l --min_count 5

# Bag-of-Bigrams on all
python eval.py main -n 2 -l --min_count 5

# Embedding on all
python eval.py main -e -l --embedding dataset/amazon_glove1600.txt
```

**'pol' dataset**
```bash
# Bag-of-Words on pol
python eval.py pol -l

# Bag-of-Bigrams on pol
python eval.py pol -n 2 -l

# Embedding on pol
python eval.py pol -e -l --embedding dataset/amazon_glove1600.txt
```

## Run the proposed models
**'pol' dataset**

VADER sentiment analysis scores

```bash
python turn-level-sentiment.py pol
```

---

## Original Readme
Evaluation code for the Self-Annotated Reddit Corpus (SARC).
  * [LREC Paper](http://www.lrec-conf.org/proceedings/lrec2018/pdf/160.pdf)
  * [SARC Files](http://nlp.cs.princeton.edu/SARC/2.0/)
  
Dependencies: NLTK, scikit-learn, text_embedding.

To recreate the all-balanced and pol-balanced results in Table 2 of the paper:

1. download [1600-dimensional Amazon GloVe embeddings](http://nlp.cs.princeton.edu/DisC/amazon_glove1600.txt.bz2) (NOTE: 2.4 GB compressed)
  
2. set the root directory of the SARC dataset at the top of <tt>utils.py</tt>
  
3. run the following (<tt>$EMBEDDING</tt> is the file of downloaded GloVe embeddings)
  * Bag-of-Words on all: <tt>python SARC/eval.py main -l --min_count 5</tt>
  * Bag-of-Bigrams on all: <tt>python SARC/eval.py main -n 2 -l --min_count 5</tt>
  * Embedding on all: <tt>python SARC/eval.py main -e -l --embedding $EMBEDDING</tt>
  * Bag-of-Words on pol: <tt>python SARC/eval.py pol -l</tt>
  * Bag-of-Bigrams on pol: <tt>python SARC/eval.py pol -n 2 -l</tt>
  * Embedding on pol: <tt>python SARC/eval.py pol -e -l --embedding $EMBEDDING</tt>

If you find this code useful please cite the following:

    @inproceedings{khodak2018corpus,
      title={A Large Self-Annotated Corpus for Sarcasm},
      author={Khodak, Mikhail and Saunshi, Nikunj and Vodrahalli, Kiran},
      booktitle={Proceedings of the Linguistic Resource and Evaluation Conference (LREC)},
      year={2018}
    }
