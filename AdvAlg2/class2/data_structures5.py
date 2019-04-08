import re
from operator import itemgetter

def get_lines(nlines):
    lines = []
    for i in range(nlines):
        lines.append(input())
    return lines


# data = played, wins, losses, goal_scored, goal_against, points, name
def compute(data, game):
    info = re.split('[#,@]', game) # split game result in # or @

    data[info[0]][0] += 1 # games played
    data[info[0]][3] += int(info[1]) #goals scored
    data[info[0]][4] += int(info[2]) #goals against
    data[info[0]][7] += int(info[1]) - int(info[2]) # goal difference

    data[info[3]][0] += 1 # games played
    data[info[3]][3] += int(info[2]) #goals scored
    data[info[3]][4] += int(info[1]) #goals against
    data[info[3]][7] += int(info[2]) - int(info[1]) # goal difference

    if int(info[1]) > int(info[2]): # team 1 won
        data[info[0]][1] += 1
        data[info[0]][5] += 3
        data[info[3]][2] += 1
    elif int(info[1]) < int(info[2]): # team 2 won
        data[info[0]][2] += 1
        data[info[3]][5] += 3
        data[info[3]][1] += 1
    else: # tie
        data[info[0]][5] += 1
        data[info[3]][5] += 1

    return data


def print_results(sortable_data, tournament_name):
    rank = 1
    print(tournament_name)
    for i in range(len(sortable_data)):
        team = sortable_data[i]
        print(str(rank) + ') ' +
              str(team[6]) + ' ' +
              str(team[5]) + 'p, ' +
              str(team[0]) + 'g (' +
              str(team[1]) + '-' +
              str(team[0] - team[1] - team[2]) + '-' +
              str(team[2]) + '), ' +
              str(team[3] - team[4]) + 'gd (' +
              str(team[3]) + '-' + str(team[4]) + ')'
             )
        rank += 1


def solve(teams_names, games_results, tournament_name):
    data = {}
    sortable_data = []

    for team in teams_names:
        data[team] = [0, 0, 0, 0, 0, 0, team, 0]

    for game in games_results:
        data = compute(data, game)

    for team in teams_names:
        sortable_data.append(data[team])

# data = played, wins, losses, goal_scored, goal_against, points, name
    sortable_data.sort(key=itemgetter(5,1,7,3), reverse = True)
#    sortable_data.sort(key=itemgetter(0, 6))
    print_results(sortable_data, tournament_name)


tournaments = int(input())

for i in range(tournaments):
    tournament_name = input()
    nteams = int(input())
    teams_names = get_lines(nteams)
    ngames = int(input())
    games_results = get_lines(ngames)
    solve(teams_names, games_results, tournament_name)
    if i < tournaments-1:
        print()
