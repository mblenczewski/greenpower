from typing import Iterable, Iterator
from itertools import islice, chain


def batch(iterable: Iterable, item_count: int = 1) -> Iterable:
    """
    Converts a given iterable input into an iterable consisting of 'batches' of elements with item_count items
    per batch. Doesn't discard incomplete batches.
    :param iterable:
        The iterable whose items should be batched.
    :param item_count:
        The number of items per batch.
    :return:
        The batched iterable.
    """
    source_iter: Iterator = iter(iterable)
    while True:
        batch_iter: Iterator = islice(source_iter, item_count)
        try:
            yield chain([next(batch_iter)], batch_iter)
        except StopIteration:
            return
