-module(matrixmult).
-export([dotProduct/2, transpose/1, formProductMatrixRow/2,
         multiply/2, pMultiply/2, formProductMatrixRowWorker/4,
         pMultiplyDemo/0, multiplyDemo/0]).

dotProduct(Vec1, Vec2) ->
  Products = lists:zipwith((fun(X,Y) -> X*Y end), Vec1, Vec2),
  lists:foldr(fun(P, Total) -> P + Total end, 0, Products).

transpose([[]|_]) ->
  [];
transpose(Matrix) ->
  [lists:map((fun(L) -> hd(L) end), Matrix)
  | transpose(lists:map((fun(L) -> tl(L) end), Matrix))].

formProductMatrixRow(Vec, M) ->
  lists:map(fun(V) -> dotProduct(V, Vec) end, M).

% Sequential matrix multiplication function
multiply(M1, M2) ->
  Transposed = transpose(M2),
  lists:map(fun(V) -> formProductMatrixRow(V, Transposed) end, M1).

% Collects results from the processes that form the rows of the product matrix
collectResult(0) ->
  [];
collectResult(Rows) ->
  receive
    RowResult -> [ RowResult | collectResult(Rows - 1) ]
  end.

% Forms one row of the product matrix and sends the row and its index in the
% product matrix back to the original process.
formProductMatrixRowWorker(Vec, M, Index, Pid) ->
  Row = formProductMatrixRow(Vec, M),
  Pid ! {Row, Index}.

% Parallel matrix multiplication function. The second matrix is transposed
% because rows are easier to handle than columns. When the rows are
% collected, the result is a list of (row, index) tuples. The list is first
% sorted by the indices and finally the indices are mapped out to produce the
% actual product matrix.
pMultiply(M1, M2) ->
  Rows = length(M1),
  Transposed = transpose(M2),
  lists:foldl(fun(Row, Index) ->
                spawn(matrixmult, formProductMatrixRowWorker, [Row, Transposed, Index, self()]),
                Index + 1
              end, 0, M1),
  IntermediateResult = collectResult(Rows),
  SortedResult = lists:sort(fun({_,I1}, {_, I2}) -> I1 =< I2 end, IntermediateResult),
  lists:map(fun({Row,_}) -> Row end, SortedResult).

% Functions for demoing
create100by100Matrix() ->
  Row = lists:seq(1,100),
  lists:duplicate(100, Row).

% Function for checking how much time it takes for a function
% to process two 100x100 matrices.
timeMatrixMultiplicationFunction(MultFunctionName) ->
  M = create100by100Matrix(),
  {Time, _} = timer:tc(matrixmult, MultFunctionName, [M,M]),
  Time.

pMultiplyDemo() ->
  timeMatrixMultiplicationFunction(pMultiply).

multiplyDemo() ->
  timeMatrixMultiplicationFunction(multiply).
