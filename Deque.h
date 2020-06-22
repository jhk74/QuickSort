
// Deque.h                                      Stan Eisenstat (02/26/20)
//
// Define the abstract data type for a Deque (*) of string pointers.  The
// strings themselves are NOT stored.
//
//   (*) A deque (or double-ended queue, pronounced "deck") is a data structure
//   that combines the attributes of a queue and a stack:  items can be added
//   at the tail and the head but can be removed only from the head.

// Define true and false
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
// A variable of type Deque is a pointer to the struct used to implement the
// deque operations declared below.  Note that the declaration of the fields of
// that struct appears only in the file that implements these operations.  Thus
// the calling program does not know what fields have been defined and cannot
// access them; and the variable must be a pointer since the size of the struct
// is unknown.

typedef struct deque *Deque;


// The following functions are the only means of accessing a Deque data
// structure.  Each requires a pointer to a Deque variable in case it needs
// to modify the value of that variable (or more generally for uniformity).
// Each returns the status of the operation, either true (= success) or false
// (= failure; e.g., an invalid argument, an inconsistent Deque object, or a
// NULL return from malloc() / realloc()).

// Set *D to a new object of type Deque.
// Returns true if successful, false otherwise (e.g., malloc() fails).
bool createD(Deque *d);

// Return true if the Deque *D is empty, false otherwise.  The value of *D may
//   change as a result.
bool isEmptyD(Deque *d);

// Add the string pointer S to the tail of the Deque *D; the string itself is
//   not duplicated.  The value of *D may change as a result.
// Return true if successful, false otherwise (e.g., malloc() fails).
bool addD(Deque *d, char *s);

// Remove the string pointer at the head of the Deque *D and store that value
//   (or NULL if the Deque is empty) in *S.  The value of *D may change as a
//   result.
// Return true if successful, false otherwise (e.g., *D is empty).
bool remD(Deque *d, char **s);

// Store in *S the value of the string pointer at the head of the Deque *D (or
//   NULL if the Deque is empty).  The value of *D may change as a result.
// Return true if successful, false otherwise (e.g., *D is empty).
bool headD(Deque *d, char **s);

// Add the string pointer S to the head of the Deque *D; the string itself is
//   not duplicated.  The value of *D may change as a result.
// Return true if successful, false otherwise (e.g., malloc() fails).
bool pushD(Deque *d, char *s);

// An alternate name for remD() when the Deque is used as a stack.
#define popD(d,s)  remD(d,s)

// An alternate name for headD() when the Deque is used as a stack.
#define topD(d,s)  headD(d,s)

// Destroy the Deque *D by freeing any storage that it uses (but not the blocks
//   of storage to which the string pointers point) and set the value of *D to
//   NULL.
// Return true if successful, false otherwise (e.g., D is an invalid argument).
bool destroyD(Deque *d);
