python-xgrab
============


## Installation

```
pip install git+https://github.com:ecarrara/python-xgrab.git#egg=xgrab
```

## Usage

```
import matplotlib.pyplot as plt
import xgrab

screen = xgrab.grab_screen(0, 0, 800, 800)

plt.imshow(screen, interpolation='nearest')
plt.show()
```

