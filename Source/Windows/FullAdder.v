module FullAdder(A, B, S, Cin, Cout);

  input A;
  input B;
  input Cin;
  output Cout;
  output S;

  wire w0;
  wire w1;
  wire w2;
  wire w3;

  xor xr1 (w1, A, B);
  xor xr2 (S, w1, Cin);
  and a1 (w2, w1, Cin);
  and a2 (w3, A, B);
  or o1 (Cout, w2, w3);

endmodule
