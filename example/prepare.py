"""
:author: Arne (gojira) Simon [arne_simon@gmx.de]

If you like this software please **donate**:

|  **ETC:** 0x7bC5Ff6Bc22B4C6Af135493E6a8a11A62D209ae5
"""
import csv


def stochastic_momentum(samples):
    low = min(samples)
    high = max(samples)

    if high != low:
        return (samples[-1] - low) / (high - low)
    else:
        return samples[-1] / low


def tangente(samples):
    return (samples[-1] - samples[-2]) / 2


def avg_d(samples):
    c = len(samples)
    delta = 0

    for i in range(1, len(samples)):
        d = samples[i-1] - samples[i]
        delta += d * d

    return delta / (c * c)


with open('coindesk-bpi-USD-close_data-2010-07-18_2016-04-14.csv') as src:
    samples = [float(row["Close Price"]) for row in csv.DictReader(src)]


def floating_stochastic_momentum(steps):
    with open('{}_floating_stochastic_momentum.csv'.format(steps), 'w') as out:
        writer = csv.writer(out)
        for i in range(0, len(samples) - steps):
            writer.writerow([stochastic_momentum(samples[i: i + steps])])


floating_stochastic_momentum(13)
