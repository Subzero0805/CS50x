import csv


teams = []

with open("2018m.csv", 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        team = row["team"]
        rating = int(row["rating"])
        teams.append({team : rating})

print(teams)