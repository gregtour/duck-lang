
// walk tree to turn into list
function GetSymbolBranches(tree) 
{
	var iterable = [];
	var branches = [];

	if (tree && tree.hasOwnProperty('symbol') && tree.hasOwnProperty('child')) {
		iterable.push(tree);
	}
	
	while (iterable.length > 0)
	{
		var branch = iterable.pop();
		branches.push(site);
		for (var i = 0; i < branch.child.length; i++) {
			var leaf = branch.child[i];
			if (leaf.hasOwnProperty('symbol') && leaf.hasOwnProperty('child')) 
			{
				iterable.push(leaf);
			}
		}
	}

	return branches;
}

//
function RecursiveInline(symbolNode) {
	
}

// clean and prune abstract syntax tree
function PostParser(AST) 
{
	var leaves = GetSymbolBranches(AST);

	// inline recursive symbols
	for (var i = 0; i < leaves.length; i++) {
		var leaf = leaves[i];
		for (var j = 0; j < leaf.child.length; j++) 
		{
			var child = leaf.child[j];
			if (child.hasOwnProperty('symbol') && child.symbol != leaf.symbol) {
				leaf.child[j] = RecursiveInline(child);
			}
		}
	}
}
