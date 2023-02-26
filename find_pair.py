def find_pair_sum(nums, target):
    d={}
    f=False
    for i,e in enumerate(nums):
        if target - e in d:
            print(f"Addition Pair found ({target - e},{nums[i]})")
            f=True
        d[e] = i
    if(not f):
        print("No pair found.")

def find_pair_sub(nums,target):
    d={}
    f=False
    for i,e in enumerate(nums):
        if target + e in d:
            print(f"Subtract Pair found ({target + e},{nums[i]})")
            f=True
        d[e] = i
    if(not f):
        print("No pair found.")
    

if __name__ == "__main__":
    nums = [1,12,2,5,6,4,7,9,3,8,15]
    target = 10

    find_pair_sum(nums,target)
    find_pair_sub(nums,target)
    
    print ("Done.")
