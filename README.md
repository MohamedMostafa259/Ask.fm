# Ask.fm Console Program
**A Console Project Similar to The Ask.fm Platform**

## Table of Contents
- [Introduction](#introduction)
- [System Design](#system-design)
- [Features](#features)
- [Usage](#usage)
- [Project Demo](#project-demo)

## Introduction
Ask.fm is a console-based question-and-answer system that allows users to ask questions and receive answers. This project operates as a file-based system, preserving the state of users, questions, and answers every time the application is run. Multiple users can use AskMe simultaneously, allowing for parallel interactions.

## System Design
![UML Class Diagram](https://imgur.com/0Dwm5vZ)

## Features
### User Authentication
  - Login: Users can log in to their accounts using their credentials.
  - Sign up: New users can create accounts by providing their name, email, password, username, and the option to enable anonymous questions.
  - Sign Out: Users can securely sign out of their accounts.
### User Operations
  - Print Questions:
    - To Me: View questions directed to the logged-in user.
    - From Me: Display questions asked by the logged-in user.
    - Feed Questions: See a feed of all questions in the system.
  - Ask and Answer Questions:
    - Users can ask and answer questions, and the system supports thread-like discussions.
    - A parent question can have multiple follow-up questions, forming a thread.
    - If the parent question is removed, the entire thread is also deleted.
  - Delete Questions:
    - Users can delete questions they have asked, including entire threads they initiated.
### User IDs and Correctness
  - Every user and question is assigned a system-generated ID.
  - User IDs are not visible to other users on the site for privacy reasons.
  - The system enforces correctness to prevent actions like removing questions asked to someone else.
  - Users can only view and edit the details of the questions they asked.

## Usage
The Ask.fm project consists of a console-based interface where users can interact with the features mentioned above.
### Login
  - Upon launching the application, you will be prompted to log in using your existing credentials.
### User Operations
  - Navigate through the menu options to:
  - Print Questions To Me
  - Print Questions From Me
  - For anonymous questions, you will see the notation "!AQ" to indicate that the other user can see your ID when you ask such questions.
### Answer and Delete
  - You can answer questions and delete your questions as needed.
  - Updated System and User Listing
  - The system will be updated in real time as you perform various actions.
### Asking Questions
  - You can ask questions individually or within a thread, contributing to a more organized discussion.
### Sign Up
  - If you are a new user, you can create an account and start using Ask.fm.

## Project Demo
[Click Here To Watch My Project Demo](https://drive.google.com/file/d/1igRoOxVthGeiFq1XgqJrBLchj1B0L_74/view?usp=drive_link)

**____________________________________________________________________________________________________**

***Enjoy using Ask.fm to engage in meaningful discussions and answer questions from others!***
**____________________________________________________________________________________________________**
