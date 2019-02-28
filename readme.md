# Rolling Randomized Tester for get_next_line

## Usage

Put this in a folder alongside your get_next_line, like:

(root)
|--get_next_line
|--testing (this repo)

In testing:

`make filegen` > Creates the file generator

`./generate_test 42 84` > generate random test files numbered 42 to 84

`sh bencher.sh 42 84` > run the tests numbered 42 to 84
