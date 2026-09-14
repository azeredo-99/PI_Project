# Activity Club Tracker

A console application in C for a sports/activity club: practitioners log activities and follow each other, and the system reports on participation, totals and schedules.

## Domain model

- **Practitioner** — id, name, contact, age, and the list of other practitioners they follow
- **Activity** — practitioner, date, name, start time, duration, distance/units
- **ActivityPlan** — a scheduled activity between a start and end date/time

## Features

- Add/remove practitioners, activities and activity plans
- Count and list practitioners by activity type
- Compute total and average time spent per activity
- Build a combined activity/plan table per practitioner
- A follow graph between practitioners (add a follow, list who follows whom)
- Load/save all three entities to plain-text files

## Tech stack

C · Visual Studio

## Running

Open `TP/main.sln` in Visual Studio and run.

## Authors

João Meira & Guilherme Azeredo — [GitHub](https://github.com/azeredo-99) · [LinkedIn](https://www.linkedin.com/in/guilherme-azeredo-a11bb0254/)
