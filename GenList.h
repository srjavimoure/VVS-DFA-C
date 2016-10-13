/**
 * GENLIST:
 *
 * 	This data type represents and manages a array list of elements (nodes).
 * Nodes can be any kind of data type, including user-defined types.
 * 
 * 	THE LIST DOES NOT CHECK THAT ALL ITS NODES ARE OF THE SAME DATA TYPE.
 */

typedef struct ST_GenList *GenList;

/**
 *	Inits a new list.
 *
 * IN:
 *
 * 	-The step size of the list. Every time the list needs to grow in size, it
 * will add "buffer" elements.
 *
 * OUT:
 * 	-A pointer to the new list.
 */
extern GenList GenList_newGenList(int buffer);

/**
 *	Returns the buffer size of the list (step size).
 */
extern int GenList_getBuffer(GenList this);

/**
 *	Returns the size of the list (number of elements it currently holds).
 */
extern int GenList_getSize(GenList this);

/**
 *	Adds one new element to the last position of the list
 *
 * IN:
 * 	-The list you want to add the element
 * 	-The element you want added
 */
extern void GenList_add(GenList this, void *element);

/**
 * 	Removes the element in the given position.
 *
 * IN:
 * 	-The list you want to remove the element
 * 	-The position of the element you want removed
 */
extern void GenList_remove(GenList this, int position);

/**
 * 	Returns the element in the given position
 */
extern void *GenList_getElement(GenList this, int position);

/**
 *	Returns an array with all the elements of the list. This array is NOT a
 * copy, so any changes made will be reflected in the GenList.
 */
extern void *GenList_getArray(GenList this);

/**
 * 	Returns the first element of the list that is equal to the one given.
 *
 * IN:
 * 	-The list where you want to find the element.
 * 	-The element for comparison.
 * 	-The function of comparison. It must return 0 if the objects are not equal,
 * 	or any other value otherwise.
 */
extern void *GenList_getExistingObject(GenList this, void *element, char (*function)(void *a, void *b));

/**
 *	Free the unused memory of the list.
 */
extern void GenList_clearNulls(GenList this);

/**
 *	Returns the String representation of the content of the list
 */
extern char *GenList_toString(GenList this, char *(*toString)(void *element));




















