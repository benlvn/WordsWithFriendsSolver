var SPACES = [
[0, 0, 0, 4, 0, 0, 2, 0, 2, 0, 0, 4, 0, 0, 0],
[0, 0, 1, 0, 0, 3, 0, 0, 0, 3, 0, 0, 1, 0, 0],
[0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0],
[4, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 4],
[0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0],
[0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0],
[2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2],
[0, 0, 0, 3, 0, 0, 0, 5, 0, 0, 0, 3, 0, 0, 0],
[2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2],
[0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0],
[0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0],
[4, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 4],
[0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0],
[0, 0, 1, 0, 0, 3, 0, 0, 0, 3, 0, 0, 1, 0, 0],
[0, 0, 0, 4, 0, 0, 2, 0, 2, 0, 0, 4, 0, 0, 0]
]

types = ['--', 'DL', 'TL', 'DW', 'TW', 'ST'];

var words_dict = {}

var fill_words_dict = function() {
	for(i = 0; i < words.length; i++){
		words_dict[words[i]] = 1
	}
}

var lookup_word = function(word) {
	return (words_dict[word] == 1)
}

var lookup_word_slow = function(word) {
	var lam = function(to_find){
		return to_find == word
	}
	return words.find(lam) != undefined
}



var print_spaces = function() {
	for(i = 0; i < SPACES.length; i++){
		row = SPACES[i]
		rowstring = ''
		for(j = 0; j < row.length; j++){
			rowstring += (types[row[j]] + ' ');
		}
		console.log(rowstring)
	}

}

var lookup_time_test = function() {
	var d1 = new Date();
	var t1 = d1.getTime() + 0;
	for(i = 0; i < words.length; ++i){
		lookup_word_slow(words[i])
	}
	var d2 = new Date();
	var t2 = d2.getTime() + 0;
	var slow_diff = t2 - t1;

	var d3 = new Date();
	var t3 = d3.getTime() + 0;
	for(i = 0; i < words.length; ++i){
		lookup_word(words[i])
	}
	var d4 = new Date();
	var t4 = d4.getTime() + 0;
	var fast_diff = t4 - t3;

	console.log("slow time: " + slow_diff);
	console.log("fast time: " + fast_diff);
}

console.log("hello world!")


fill_words_dict()
lookup_time_test()

console.log("goodbye world!")




