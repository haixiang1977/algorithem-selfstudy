// Forward lists are sequence containers that allow constant time insert and erase operations anywhere within the sequence.
// Forward lists are implemented as singly-linked lists
// The main design difference between a forward_list container and a list container is that the first keeps internally only a link to the next element,
// while the latter keeps two links per element: one pointing to the next element and one to the preceding one, allowing efficient iteration in both directions,
// but consuming additional storage per element and with a slight higher time overhead inserting and removing elements.
