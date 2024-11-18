Supermarket receipt program

Requires g++ and makefile

To run googletests run "make test"

To run program run "make checkout" then "./checkout" then follow prompt.
Barcodes are saved in product catalog csv file.
You can add to product catalog by following variable types.
Adding 3+ products that have a BTGO (buy two get one) or Bulk Sale (3+ items
with the same sale tag) adds an item that marks the sale.

To clean folder run "make clean"

Folders './src' and './tests' contain program source files and test files

Limited by time to complete testing for test_UI and test_productDatabase