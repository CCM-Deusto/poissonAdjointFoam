Jy = 0.5*gSum( volField * ( Foam::pow( y.internalField() - yd.internalField(), 2 ) ) );

Ju = 0.5*gSum( volField * ( beta * Foam::pow( u.internalField(), 2 ) ) );

J = Jy + Ju;

/*
J = 0.5*gSum( volField * ( Foam::pow( y.internalField() - yd.internalField(), 2 ) \
 + beta * Foam::pow( u.internalField(), 2 ) ) );
*/
