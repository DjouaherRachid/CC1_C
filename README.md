
# CC1

## Contributors
Djouaher Rachid, 3SI3

## Compilation

To compile the project, run the following command:

```bash
make
```

This will generate an executable named `db`.

## Running the Database

Once compiled, you can run the database using:

```bash
./db
```

### Available Commands

1. **.exit**  
   Exit the database program.
   
   Example:
   ```
   db > .exit
   ```

2. **insert**  
   Insert a row into the database with a given `id` and `name`.
   
   Example:
   ```
   db > insert 1 Rachid
   ```

3. **select**  
   Select rows from the database:
   
   - **Select all rows**:
     ```
     db > select *
     ```
   
   - **Select a row by ID**:
     ```
     db > select 1
     ```

4. **delete**  
   Delete a row from the database by `id`.
   
   Example:
   ```
   db > delete 1
   ```

5. **.save**  
   Save the current state of the database to a file.
   
   Example:
   ```
   db > .save my_database
   ```

6. **.load**  
   Load the database from a file into memory.
   
   Example:
   ```
   db > .load my_database
   ```

## File Persistence

The database supports saving to and loading from a binary file. The commands `.save` and `.load` allow you to persist data between sessions.

- Use `.save <filename>` to save the current database state to a file.
- Use `.load <filename>` to load a previously saved database file into memory.
