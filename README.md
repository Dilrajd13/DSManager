# DSManager

A terminal for creating, editing and visualizing data structures, written in C++. You type commands inspired by the Linux terminal, and it redraws the structure after every change so you can see how it behaves.

## Supported data structures

| Type | Command name | Removes | Display |
|---|---|---|---|
| Linked list | `LL` | Any value you choose | `a-->b-->c-->NULL` |
| Stack | `stack` | The newest value | Vertical, top to bottom |
| Queue | `queue` | The oldest value | `FRONT -> [a] [b] <- BACK` |
| Min heap | `heap` | The smallest value | Array and tree |
| Binary search tree | `tree` | Any value you choose | Tree and in-order list |

## Example

```
DSMNGR>>> new tree numbers
Created BinaryTree numbers
DSMNGR>>> add numbers 50
DSMNGR>>> add numbers 30
DSMNGR>>> add numbers 70
DSMNGR>>> add numbers 20
DSMNGR>>> add numbers 40
DSMNGR>>> view numbers
50
|-- L: 30
|   |-- L: 20
|   `-- R: 40
`-- R: 70
In order: 20 30 40 50 70
```



## Commands

| Command | What it does |
|---|---|
| `help` | Shows the list of commands |
| `DSLS` | Lists every data structure you made, like `ls` |
| `new <type> <name>` | Makes a data structure |
| `view <name>` | Draws a data structure |
| `add <name> <value>` | Adds a value |
| `add <name> <value> head` | Adds to the front of a linked list |
| `remove <name>` | Removes the next value from a stack, queue or heap |
| `remove <name> <value>` | Removes a value from a linked list or tree |
| `search <name> <value>` | Checks if a value is in a data structure |
| `edit <name> <old> <new>` | Replaces a value in a linked list, heap or tree |
| `rm <name>` | Deletes a whole data structure |
| `exit` | Closes the program |



