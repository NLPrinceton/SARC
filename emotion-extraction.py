
# Import module
from nrclex import NRCLex

# Assign list of strings
text = ['sounds', 'fun', 'though']

# Iterate through list
for i in range(len(text)):

    # Create object
    emotion = NRCLex(text[i])

    # Classify emotion
    print('\n\n', text[i], ': ', emotion.top_emotions)