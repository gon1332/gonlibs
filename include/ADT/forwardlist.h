#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <stdbool.h>
#include <stdint.h>

/*!
 * \file forwardlist.h
 * \brief Interface of the forwardlist ADT
 *
 */

#define T forwardlist_t
typedef struct T *T;

typedef void *forwardlist_iterator_t;

/*! \brief **Construct forwardlist object**
 *
 * \details Constructs a forwardlist ADT object, initializing its contents
 *          depending on the parameter based constructor version used:
 *    1. _**Default constructor:**_ Creates an empty list.
 *    2. _**Fill constructor:**_ Creates list initialized with the given elements.
 *
 * \param elem_list A list of data that the list may hold or NULL for an empy list.
 * \return Pointer to the forwardlist.
 *
 * **Usage**
 * ~~~~{.c}
 *     forwardlist_t p1 = forwardlist_new(NULL);
 *     forwardlist_t p2 = forwardlist_new("One", "Two", "Three", NULL);
 *     forwardlist_t p3 = forwardlist_new(forwardlist_new(1),
 *                                (void *)forwardlist_new(2),
 *                                (void *)forwardlist_new(3),
 *                                (void *)forwardlist_new(4), NULL));
 * ~~~~
 *
 */
extern T forwardlist_new(void *elem, ...);


/*! \brief **Destroy forwardlist object**
 *
 * \details Destroys the forwardlist object.
 *
 * \param list
 * \return none
 *
 * **Usage**
 * ~~~~{.c}
 *     forwardlist_free(p1);
 * ~~~~
 *
 */
extern void forwardlist_free(T *list);


// Iterators
extern forwardlist_iterator_t forwardlist_begin(T list);
extern forwardlist_iterator_t forwardlist_end(T list);
extern forwardlist_iterator_t forwardlist_next(T list, forwardlist_iterator_t it);
extern void **forwardlist_deref(forwardlist_iterator_t it);


// Capacity
/*! \brief **Test whether forwardlist is empty**
 *
 * \details Returns a bool value indicating whether the forwardlist ADT is empty,
 *          i.e. whether its size is 0.
 *
 *          This function does not modify the content of the container in any way.
 *          To clear the content of an array object, see forwardlist_clear().
 *
 * \param list
 * \return `true` if the `list` size is 0, `false` otherwise.
 *
 * **Usage**
 * ~~~~{.c}
 *     if (!forwardlist_empty(p2)) {
 *         // do somehting with non-empty list
 *     } else {
 *         // do somehting with empty list
 *     }
 * ~~~~
 *
 */
extern bool forwardlist_empty(T list);


/*! \brief **Return size**
 *
 * \details Returns the number of elements in the forwardlist object.
 *
 * \param list
 * \return The number of elements in the `list`.
 *
 * **Usage**
 * ~~~~{.c}
 *     if (forwardlist_size(p2) > 0) {
 *         // do somehting with non-empty list
 *     }
 * ~~~~
 *
 */
extern uintmax_t forwardlist_size(T list);


// Modifiers
/*! \brief **Insert element at beginning**
 *
 * \details Inserts a new element at the beginning of the forwardlist, right
 *          before its current first element. The content of `elem` is copied
 *          (or moved) to the inserted element.
 *
 *          This effectively increases the container size by one.
 *
 * \param list
 * \param elem Value to be copied to the inserted element.
 * \return none
 *
 * **Usage**
 * ~~~~{.c}
 *     forwardlist_push_front(p2, "Zero");
 * ~~~~
 *
 */
extern void forwardlist_push_front(T list, void *elem);


/*! \brief **Delete first element**
 *
 * \details Removes the first element in the forwardlist, effectively reducing
 *          its size by one.
 *
 *          The removed element is returned to the user.
 *
 * \param list
 * \return The removed element.
 *
 * **Usage**
 * ~~~~{.c}
 *     forwardlist_pop_front(p2);
 * ~~~~
 *
 */
extern void *forwardlist_pop_front(T list);


extern void forwardlist_append(T list, T tail);


// extern void  forwardlist_insert_after(T list, const uintmax_t pos, void *elem);


// extern void  forwardlist_erase_after (T list, const uintmax_t pos);


/*! \brief **Apply function to content**
 *
 * \details Calls the function pointed to by `apply` for every node in forwardlist.
 *          Clients can pass an application-specific pointer, `cl`, to forwardlist_map(),
 *          and this pointer is passed along to *apply as its second argument.
 *
 * \param list
 * \param apply Pointer to the function to by applied on each content of the forwardlist.
 * \param cl    Application-specific pointer.
 * \return none
 *
 */
extern void forwardlist_map(T list,
        void apply(void **x, void *cl), void *cl);


/*! \brief **Clear content**
 *
 * \details Removes all elements from the forwardlist (which are destroyed),
 *          and leaves the forwardlist with a size of 0.
 *
 * \param list
 * \return none
 *
 */
extern void forwardlist_clear(T list);


// Operations
/*! \brief **Reverse the order of elements**
 *
 * \details Reverses the order of the elements in the forwardlist in place.
 *
 * \param list
 * \return none
 *
 * **Usage**
 * ~~~~{.c}
 *     forwardlist_reverse(p2);
 * ~~~~
 *
 */
extern void forwardlist_reverse(T list);


// extern T      forwardlist_copy    (T list);


/*! \brief **Return forwardlist as an array**
 *
 * \details Given a list with N values, forwardlist_to_array() creates an array
 *          in which elements zero through N-1 hold the N values from the first
 *          fields of the list and the Nth element holds the value of end, which
 *          is often the null pointer.
 *
 * \param list
 * \param end Holds the value of the end of the forwardlist.
 * \return The pointer to the first element of the array.
 *
 */
extern void **forwardlist_to_array(T list, void *end);

#undef T
#endif // FORWARDLIST_H
