import sys
import json

if __name__ == "__main__":
    if len(sys.argv) > 1:
        inputname = sys.argv[1]
        # print(inputname)
        get_list = {}
        with open(inputname) as json_file:
            get_list = json.load(json_file)
            if len(sys.argv) < 3:
                print(json.dumps(get_list, indent = 2))
            else:
                out_name = sys.argv[2]
                with open(out_name, 'w') as out_file:
                    json.dump(get_list, out_file, indent = 2)
    else:
        print("dumpjson.py [input file] ([output file])")
