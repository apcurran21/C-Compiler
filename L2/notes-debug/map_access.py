import gdb

# Define a convenience function to access elements of the unordered_map
def get_map_element(map_val, key):
    # Get the pointer to the key
    key_ptr = gdb.parse_and_eval('std::string("%s")' % key)
    # Access the element using the key
    element = map_val[key_ptr]
    return element