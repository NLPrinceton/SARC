# Import module
from nrclex import NRCLex
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

    train_all_docs_emo = []
    test_all_docs_emo = []
    # Measuring Emotions in each sentence
    for sentence in train_all_docs_tok:
        n_word = len(sentence)
        emo_count = {"fear": 0, "anger": 0, "anticipation": 0, "trust": 0, "surprise": 0, "positive": 0, "negative": 0, "sadness": 0, "disgust": 0, "joy": 0}
        for word in sentence:
            emotion = NRCLex(word).raw_emotion_scores
            for emo in emotion:
                emo_count[emo] += 1
        train_all_docs_emo.append([emo_count["fear"]/n_word, emo_count["anger"]/n_word, emo_count["anticipation"]/n_word, emo_count["trust"]/n_word, emo_count["surprise"]/n_word, emo_count["positive"]/n_word, emo_count["negative"]/n_word, emo_count["sadness"]/n_word, emo_count["disgust"]/n_word, emo_count["joy"]/n_word])
    train_all_docs_emo = np.array(train_all_docs_emo)

    for sentence in test_all_docs_tok:
        n_word = len(sentence)
        emo_count = {"fear": 0, "anger": 0, "anticipation": 0, "trust": 0, "surprise": 0, "positive": 0, "negative": 0, "sadness": 0, "disgust": 0, "joy": 0}
        for word in sentence:
            emotion = NRCLex(word).raw_emotion_scores
            for emo in emotion:
                emo_count[emo] += 1
        test_all_docs_emo.append([emo_count["fear"]/n_word, emo_count["anger"]/n_word, emo_count["anticipation"]/n_word, emo_count["trust"]/n_word, emo_count["surprise"]/n_word, emo_count["positive"]/n_word, emo_count["negative"]/n_word, emo_count["sadness"]/n_word, emo_count["disgust"]/n_word, emo_count["joy"]/n_word])
    test_all_docs_emo = np.array(test_all_docs_emo)

    # Evaluate this classifier on all responses.
    print('Evaluate the classifier on all responses')
    clf = LogitCV(Cs=[10**i for i in range(-2, 3)], fit_intercept=False, cv=2, dual=np.less(*train_all_docs_emo.shape), solver='liblinear', n_jobs=-1, random_state=0)
    clf.fit(train_all_docs_emo, train_all_labels)
    print('\tTrain acc: ', clf.score(train_all_docs_emo, train_all_labels))
    print('\tTest acc: ', clf.score(test_all_docs_emo, test_all_labels))

    # Get vectors for first and second responses.
    n_tr = int(train_all_docs_emo.shape[0]/2)
    n_te = int(test_all_docs_emo.shape[0]/2)
    train_vecs = {i: train_all_docs_emo[i*n_tr:(i+1)*n_tr,:] for i in range(2)}
    test_vecs = {i: test_all_docs_emo[i*n_te:(i+1)*n_te,:] for i in range(2)}

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