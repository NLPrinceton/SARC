from eval import parse, preprocessing
from sklearn.linear_model import LogisticRegressionCV as LogitCV
from text_embedding.features import *
from text_embedding.vectors import *
from utils import *

def main():
    args = parse()
    if args.dataset.lower() == 'pol':
        SARC = SARC_POL
    elif args.dataset.lower() == 'main':
        SARC = SARC_MAIN

    train_file = SARC+'train-balanced.csv'
    test_file = SARC+'test-balanced.csv'
    comment_file = SARC+'comments.json'

    # Load SARC pol/main sequences with labels.
    print('Load SARC data')
    train_seqs, test_seqs, train_labels, test_labels = \
        load_sarc_responses(train_file, test_file, comment_file, lower=args.lower)

    # Only use responses for this method. Ignore ancestors.
    train_resp = train_seqs['responses']
    test_resp = test_seqs['responses']

    # Split into first and second responses and their labels.
    # {0: list_of_first_responses, 1: list_of_second_responses}
    train_docs = {i: [l[i] for l in train_resp] for i in range(2)}
    test_docs = {i: [l[i] for l in test_resp] for i in range(2)}
    train_labels = {i: [2*int(l[i])-1 for l in train_labels] for i in range(2)}
    test_labels = {i: [2*int(l[i])-1 for l in test_labels] for i in range(2)}

    # Train a classifier on all responses in training data. We will later use this
    # classifier to determine for every sequence which of the 2 responses is more sarcastic.
    train_all_docs_tok = preprocessing(tokenize(train_docs[0] + train_docs[1]))
    test_all_docs_tok = preprocessing(tokenize(test_docs[0] + test_docs[1]))
    train_all_labels = np.array(train_labels[0] + train_labels[1])
    test_all_labels = np.array(test_labels[0] + test_labels[1])

    # create baf of n-grams
    print('Create bongs')
    n = args.n
    min_count = args.min_count
    train_ngrams = [sum((list(nltk.ngrams(doc, k)) for k in range(1, n+1)), []) for doc in train_all_docs_tok]
    test_ngrams = [sum((list(nltk.ngrams(doc, k)) for k in range(1, n+1)), []) for doc in test_all_docs_tok]
    vocabulary = feature_vocab(train_ngrams, min_count=min_count)
    train_all_vecs = docs2bofs(train_ngrams, vocabulary)
    test_all_vecs = docs2bofs(test_ngrams, vocabulary)

    # Normalize?
    if args.normalize:
        normalize(train_all_vecs, copy=False)
        normalize(test_all_vecs, copy=False)
    print('Dimension of representation: %d'%train_all_vecs.shape[1])

    # Evaluate this classifier on all responses.
    print('Evaluate the classifier on all responses')
    clf = LogitCV(Cs=[10**i for i in range(-2, 3)], fit_intercept=False, cv=2, dual=np.less(*train_all_vecs.shape), solver='liblinear', n_jobs=-1, random_state=0)
    clf.fit(train_all_vecs, train_all_labels)
    print('\tTrain acc: ', clf.score(train_all_vecs, train_all_labels))
    print('\tTest acc: ', clf.score(test_all_vecs, test_all_labels))

    # Get vectors for first and second responses.
    n_tr = int(train_all_vecs.shape[0]/2)
    n_te = int(test_all_vecs.shape[0]/2)
    train_vecs = {i: train_all_vecs[i*n_tr:(i+1)*n_tr,:] for i in range(2)}
    test_vecs = {i: test_all_vecs[i*n_te:(i+1)*n_te,:] for i in range(2)}

    # Final evaluation.
    print('Evaluate the classifier on the original dataset')
    hyperplane = clf.coef_[0,:]
    train_pred_labels = 2*(train_vecs[0].dot(hyperplane) > train_vecs[1].dot(hyperplane))-1
    test_pred_labels = 2*(test_vecs[0].dot(hyperplane) > test_vecs[1].dot(hyperplane))-1
    train_expect_labels = train_labels[0]
    test_expect_labels = test_labels[0]
    print('\tTrain acc: ', (train_pred_labels == train_expect_labels).sum() / train_pred_labels.shape[0])
    print('\tTest acc: ', (test_pred_labels == test_expect_labels).sum() / test_pred_labels.shape[0])

main()