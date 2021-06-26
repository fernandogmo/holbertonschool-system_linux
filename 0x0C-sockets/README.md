# 0x0C. Sockets.

The goal of this project is to build a simple HTTP REST API in C.

This is going to be a really simple API, allowing us to manage a list of things to do (a.k.a a TODO list). Our database will be the RAM, meaning we won’t have any persistent storage. It’s not the purpose of this project anyway. Every time you start your server, the list of todos is empty.

A `todo` contains at least the following fields:

- `id` -> Positive integer, starting from `0`
- `title` -> String
- `description` -> String


Here are the different routes that will have to be implemented:

- `/todos`
  - `POST` -> Creates a new todo
  - `GET` -> Retrieve all the todos
- `/todos?id={id}` (where `{id}` is a positive integer)
  - `GET` -> Retrieve the todo with the corresponding id
  - `DELETE` -> Delete the todo with the corresponding id
