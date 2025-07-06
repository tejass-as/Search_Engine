# 🔍 Optimized Search Engine Using Trie and Splay Trees

### 📘 Advanced Data Structures Project  
**Developed by:**  
- Tejas Sonawane (612203170)  
- Isha Wagh (612203191)

---

## 📌 Project Overview

This project implements an **optimized question search engine** that provides **efficient query handling, autosuggestions, history tracking, and frequency analysis** using two powerful data structures: **Trie** and **Splay Tree**.

---

## 🚀 Features

- 🔎 Search questions
- 🧠 Autosuggestions based on prefixes
- 📜 Recently searched question tracking
- 📂 Search history display
- 📊 Most/least frequently searched question tracking
- 🧹 History clearing

---

## 🧱 Data Structures Used

### ✅ Trie
- Efficient for **prefix-based search** and **autocomplete**
- Stores questions character-by-character
- Supports **case-insensitive** and **space-aware** searches

### ✅ Splay Tree
- **Self-adjusting binary search tree**
- Moves recently/frequently accessed items to the top
- Used for maintaining **search history and frequency**

---

## 🧩 Key Components

| Component                  | Data Structure | Functions                                                  | Purpose                                                                 |
|----------------------------|----------------|------------------------------------------------------------|-------------------------------------------------------------------------|
| **Trie Implementation**    | Trie           | `insert_from_file()`, `search()`, `suggestions()`          | Exact match and prefix-based search with autocomplete suggestions      |
| **Splay Tree Implementation** | Splay Tree     | `insert_freq()`, `splay_freq()`, `load_from_file_freq()`    | Adjusts tree based on frequency; stores and updates search frequencies |
| **Frequency Analysis**     | Splay Tree     | `print_max()`, `print_min()`, `frequency()`                 | Provides most/least searched questions and analytics                   |
| **Helper Functions**       | —              | `remove_spaces()`, `isLastNode()`, `preorder_freq()`        | Utility functions for text handling and debugging                      |

---

## ⚙️ Operations and Complexities

| Operation              | Command        | Implementation                      | Time Complexity     |
|------------------------|----------------|-------------------------------------|---------------------|
| Search a question      | `-s`           | Trie search + Splay update          | O(L)                |
| Autosuggestions        | `-a <prefix>`  | Trie traversal                      | O(L + k)            |
| Recent search          | `-r`           | Splay Tree root access              | O(1)                |
| Display history        | `-h`           | Splay Tree traversal                | O(n)                |
| Most/Least frequent    | `-fm` / `-fl`  | Frequency analysis via traversal    | O(n)                |
| Clear search history   | `-d`           | Splay Tree reset                    | O(1)                |

---

## 🌐 Real-World Applications

- 🔍 Web search engines (e.g., Google, Bing)
- 🧠 Spell checkers and auto-correct tools
- 🧾 Browser history and command recall
- 💬 Messaging apps with predictive suggestions
- 📇 Contact lists with search
- 🌍 DNS routing and IP prefix matching
- 🗃️ Database indexing for performance optimization

---

## ✅ Advantages

- 🚀 Fast search and autosuggestion operations
- 🧠 Intelligent access to frequent and recent queries
- 💾 Memory-efficient for questions with common prefixes

---

## ❌ Limitations

- 🧠 Higher memory usage for large Trie datasets
- ⚙️ Complexity in combining and managing data structures

---

## 📊 Performance

- **Search speed**: O(L) (where L is the length of the question)
- **Autosuggestions**: O(L + k) (L = prefix length, k = number of suggestions)
- **History retrieval**: O(1)

---

## ✅ Conclusion

- **Trie** enables fast and efficient prefix-based searching.
- **Splay Tree** ensures optimized history and frequency tracking.
- The **combined approach** results in a **high-performance search engine**.

---

## ❓ Questions / Feedback?

Feel free to reach out for any queries or improvements.  
**Thank you for checking out our project!**
