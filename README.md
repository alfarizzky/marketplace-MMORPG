# 🛒 Marketplace Game – Multi Linked List (C++)

<div align="center">

<img src="https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=c%2B%2B" />
<img src="https://img.shields.io/badge/Data%20Structure-Multi%20Linked%20List-orange?style=for-the-badge" />
<img src="https://img.shields.io/badge/Type-Console%20Application-lightgrey?style=for-the-badge" />

### *Console-Based Marketplace Simulation using Multi Linked List*

📦 **Data Structures Final Project**  
🎮 **Case Study: Game Marketplace (Player & Item)**

</div>

---

## 📌 Overview

**Marketplace Game** is a **C++ console application** that simulates a simple in-game marketplace system.  
It applies the **Multi Linked List** data structure to manage relationships between:

- **Players** (Parent)
- **Items** (Child)
- **Ownership Relations**

This project was developed as part of an academic assignment for the **Data Structures** course, focusing on pointer-based data structures and relational lists.

---

## ✨ Main Features

<table>
<tr>
<td width="33%" align="center">

### 👤 Player Management  
Create, search, login, and delete players  
<sub>Gold • Income • Outcome</sub>

</td>
<td width="33%" align="center">

### 🧩 Item Management  
Sell, delete, search, and display items  
<sub>Weapon / Non-Weapon</sub>

</td>
<td width="33%" align="center">

### 🔗 Dynamic Relations  
Multi Linked List relations  
<sub>Transfer ownership • Count relations</sub>

</td>
</tr>
</table>

---

## 🧠 Data Structure Design

The system is implemented using a **Multi Linked List** data structure consisting of three main components:
**Parent**, **Relation**, and **Child**.

<div align="center">

<img src="structureDesign.png" alt="Multi Linked List Structure Design" width="90%"/>

</div>

### 🔹 Description

- **Parent List (Player)**  
  Stores all players in the marketplace.  
  Each player node contains player information and a pointer to its own relation list.

- **Relation List**  
  Acts as a connector between players and items.  
  Each relation node stores a pointer to a child (item) owned by the player.

- **Child List (Item)**  
  Stores all items globally in the marketplace.  
  Items are stored only once and ownership is managed through relation nodes.

### 🔹 Relationship Flow

```text
Player (Parent)
   |
   v
Relation List
   |
   v
Item (Child)
```

This design allows:
- One player to own multiple items
- Items to be managed independently from ownership
- Easy ownership transfer by modifying relation nodes only
- No duplication of item data

The structure fully follows the **Multi Linked List** concept commonly used in Data Structures courses.

---

## 🧩 Functionalities

### 🔐 Login System
- Login using username
- One active player per session

### 🛒 Marketplace System
- Sell items
- Buy items between players
- Gold and ownership validation

### 📊 Statistics
- Player with highest gold
- Player with highest total spending
- Items without any owner
- Number of relations per player

### 🔍 Searching
- Search player by username
- Search item by name
- Find item owner

---

## 🚀 How to Run

### Requirements
```
C++ Compiler (g++ / clang)
Terminal / Command Prompt
```

### Compile & Execute
```bash
g++ main.cpp marketplace.cpp -o marketplace
./marketplace
```

---

## 🧭 Main Menu

```
1. Insert Player
2. Login
3. Show Market
4. Statistics Menu
5. Search Player
6. Delete Player
0. Exit
```

## 👤 Player Menu

```
1. Player Info
2. Show Owned Items
3. Sell Item
4. Add Relation
5. Delete Relation
6. Delete Item
7. Transfer Item Ownership
8. Search Item
9. Find Item Owner
10. Buy Item
11. Relation Count Menu
0. Logout
```

---

## 📁 Project Structure

```
marketplace/
│
├── marketplace.h      # Structs & function declarations
├── marketplace.cpp    # Function implementations
├── main.cpp           # Main program & menus
└── README.md
```

---

## 🔬 Implementation Notes

- Uses **dynamic memory allocation**
- No STL containers (vector, list, map, etc.)
- Relations implemented as linked lists inside parent nodes
- Input validation for critical operations
- Suitable as a **Multi Linked List reference project**

---

## 👥 Authors

<div align="center">

<table>
<tr>

<td align="center" width="33%">
<a href="https://github.com/alfarizzky">
<img src="https://github.com/alfarizzky.png" width="100px"/><br/>
<b>FLY</b>
</a><br/>
<sub>Repository Owner & Core Developer</sub>
</td>

<td align="center" width="33%">
<a href="https://github.com/rizkidsaputra">
<img src="https://github.com/rizkidsaputra.png" width="100px"/><br/>
<b>Rizki D. Saputra</b>
</a><br/>
<sub>Core Developer</sub>
</td>

<td align="center" width="33%">
<a href="https://github.com/ikan999">
<img src="https://github.com/ikan999.png" width="100px"/><br/>
<b>FIZ</b>
</a><br/>
<sub>Core Developer</sub>
</td>

</tr>
</table>

</div>


---

## ⚠️ Disclaimer

This project was developed collaboratively as an academic assignment  
for the **Data Structures** course.

All contributors participated equally in the design and implementation.

