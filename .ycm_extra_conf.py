CXXFLAGS = '-Wall -std=c++1y'.split()

FLAGS = {
        'flags': CXXFLAGS
        }

def FlagsForFile(filename, **kwargs):
    return FLAGS

