Yeah, clearly a cleanup is in order. 

Pinmuxing should be centralized, naming should be fixed...

Runtime organization.

Two components: userspace and PRU.

PRU: records quadrature; emits events.

SHOULD: pop out reports, eat settings?

let's do all motor control in userspace for now; we're not going to
beat that speed anyway 
