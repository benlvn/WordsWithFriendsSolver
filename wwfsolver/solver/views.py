from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
import json
from django.views.decorators.csrf import csrf_exempt
import subprocess

# Create your views here.
def index(request):
	return render(request, 'solver/index.html')

# Parses the UI data into a dictionary:
#	board - 2D array of tiles on board
#	rack - 1D array of the racked tiles
def parse_solve_req(solve_request):
	parsed = {}
	rack = []
	for tile in solve_request['rack[]']:
		rack += [tile.encode('utf-8')]
	parsed['rack'] = rack

	board = []
	for i in range(15):
		key = 'board[' + str(i) + '][]'
		next_row = []
		for space in solve_request[key]:
			next_row += [space.encode('utf-8')]
		board += [next_row]
	parsed['board'] = board
	return parsed

def solve(request):

	game_board = request.GET.get('board')
	myDict = dict(request.GET)

	# Input to backend is a 1D list
	# The letter (or lack thereof) of each tile is recorded left to right, then top to bottom
	# Then each letter in the rack is appended
	backend_input = []
	rec_info = parse_solve_req(myDict)
	for row in rec_info["board"]:
		backend_input += row
	backend_input += rec_info["rack"]

	# Run backend
	# Record output in outfile.txt
	with open('solver/outfile.txt', 'w') as outfile:
		subprocess.call(["./solver/functionality/main"] + backend_input)

	# FOR TESTING
	# Print output
	with open('solver/outfile.txt', 'r') as outfile:
		for line in outfile:
			print(line)

	# rack = request.GET.get('rack')
	# print(rack)
	# json_data = json.loads(request.body)
	# print(json_data)
	print("\nDone\n\n")
	print(parse_solve_req(myDict))
	print("Actually done")


	# Return success
	return JsonResponse({'success':'yes'})
