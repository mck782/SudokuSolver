"""Following tutorial from OpenCV Python tutorial, basic OCR example.

source: http://opencv-python-tutroals.readthedocs.org/en/latest/py_tutorials/py_ml/py_knn/py_knn_opencv/py_knn_opencv.html
"""
import os
import sys

import cv2
from matplotlib import pyplot as plt
import numpy as np


def show_image(image):
    """Show a closable image."""
    cv2.imshow('image', image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


def create_model(train_features, train_labels):
    """Create and train a KNN model."""
    print 'Creating model'
    knn = cv2.KNearest()
    knn.train(train_features, train_labels)
    return knn


def compute_accuracy(knn, test_features, test_labels):
    """Print accuracy of given KNN data model."""
    print 'Computing accuracy'
    ret,result,neighbours,dist = knn.find_nearest(test_features, k=5)
    
    matches = result==test_labels
    correct = np.count_nonzero(matches)
    accuracy = correct*100.0/result.size
    print accuracy
    return accuracy


def resize_and_flatten(img, x=20.0, y=20.0):
    """Resize given image proportionally and flatten it out."""
    row, col = img.shape
    res = cv2.resize(img, None, fx=(x/col), fy=(y/row), interpolation = cv2.INTER_CUBIC)
    res = res.reshape(-1,400).astype(np.float32) # Size = (2500,400)
    return res


def read_digits():
    """Read in digits and parse accordingly."""
    print 'Reading digits'
    img = cv2.imread('digits.png')
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    
    # Now we split the image to 5000 cells, each 20x20 size
    cells = [np.hsplit(row,100) for row in np.vsplit(gray,50)]

    # Make it into a Numpy array. It size will be (50,100,20,20)
    x = np.array(cells)

    # Now we prepare train_data and test_data.
    train_features = x[:,:50].reshape(-1,400).astype(np.float32) # Size = (2500,400)
    test_features = x[:,50:100].reshape(-1,400).astype(np.float32) # Size = (2500,400)

    # Create labels for train and test data
    k = np.arange(10)
    train_labels = np.repeat(k,250)[:,np.newaxis]
    test_labels = train_labels.copy()
    return train_features, train_labels, test_features, test_labels


def load_data():
    """Load up data sets."""
    print 'Loading model'
    with np.load('knn_data.npz') as data:
        train_features = data['train']
        train_labels = data['train_labels']
        test_features = data['test']
        test_labels = data['test_labels']
    return train_features, train_labels, test_features, test_labels


def get_model():
    if 'knn_data.npz' not in os.listdir('./'):
        train_features, train_labels, test_features, test_labels = read_digits()
        knn = create_model(train_features, train_labels)
        acc = compute_accuracy(knn, test_features, test_labels)
        np.savez('knn_data.npz',train=train_features, train_labels=train_labels, test=test_features, test_labels=test_labels)
        print 'Saved as "knn_data.npz"'
    else:
        train_features, train_labels, test_features, test_labels = load_data()
        knn = create_model(train_features, train_labels)
    return knn


def read_number_from_file(filename):
    knn = get_model()
    # KNN is created.
    image = cv2.imread(filename)
    # show_image(image)
    gray_image = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
    image = np.negative(gray_image)

    processed_img = resize_and_flatten(image)
    # Pick nearest 5 neighbors.
    ret,result,neighbours,dist = knn.find_nearest(processed_img, k=5)
    print 'ret: ', ret
    print 'result: ', result
    print 'neighbours: ', neighbours
    print 'dist: ', dist
    print 'Done.'
    return ret


def read_number_from_image(image):
    knn = get_model()
    # KNN is created.
    gray_image = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
    image = np.negative(gray_image)
    # show_image(image)
    processed_img = resize_and_flatten(image)
    # Pick nearest 5 neighbors.
    ret,result,neighbours,dist = knn.find_nearest(processed_img, k=5)
    print 'ret: ', ret
    print 'result: ', result
    print 'neighbours: ', neighbours
    print 'dist: ', dist
    print 'Done.'
    return ret


def main():
    filename = sys.argv[1]
    read_number_from_file(filename)


if __name__ == '__main__':
    main()
