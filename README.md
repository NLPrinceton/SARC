# SARC
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
