import orb
import sift
import time
import psutil
import os

def match(method, dataset_path, results_folder, skip_matrix=False):
    start = time.time()
    process = psutil.Process(os.getpid())
    cpu_time_start = process.cpu_times()
    mem_start = process.memory_info().rss

    if method == "orb":
        orb.process_dataset(dataset_path, results_folder + "/orb", skip_matrix)
    elif method == "sift":
        sift.process_dataset(dataset_path, results_folder + "/sift", skip_matrix)
    else:
        return 0

    end = time.time()
    cpu_time_end = process.cpu_times()
    mem_end = process.memory_info().rss

    return end-start, (mem_end-mem_start) / (1000 * 1000), cpu_time_end.user-cpu_time_start.user



def main():
    dataset_path = "data_check"
    results_folder = "results_folder"

    a = match("orb", dataset_path, results_folder, True)
    b = match("sift", dataset_path, results_folder, True)
    c = match("orb", "uia_dataset", results_folder + "/uia", True)
    d = match("sift", "uia_dataset", results_folder + "/uia", True)

    with open("performance_report.txt", "w") as f:
        f.write(f"fingerprint matching:\n")
        f.write(f"orb: time used: {a[0]}ms, memory used: {a[1]}mb, CPU time: {a[2]}ms\n")
        f.write(f"sift: time used: {b[0]}ms, memory used: {b[1]}mb, CPU time: {b[2]}ms\n\n")

        f.write(f"uia campus matching:\n")
        f.write(f"orb: time used: {c[0]}ms, memory used: {c[1]}mb, CPU time: {c[2]}ms\n")
        f.write(f"sift: time used: {d[0]}ms, memory used: {d[1]}mb, CPU time: {d[2]}ms\n\n")



if __name__ == '__main__':
    main()