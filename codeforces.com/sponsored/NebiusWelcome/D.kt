private fun solveMin(s: String) : Int {
    var res = 0
    var pos = 0
    while (pos + 1 < s.length) {
        if (s[pos] == '1' && s[pos + 1] == '1') {
            pos++
            res++
        }
        pos++
    }
    return s.count { it == '1' } - minOf(s.length / 4, res)
}
private fun solveMax(s: String) : Int {
    var res = 0
    var pos = 0
    while (pos + 1 < s.length) {
        if (s[pos] == '0' || s[pos + 1] == '0') {
            pos++
            res++
        }
        pos++
    }
    return s.count { it == '1' } - (s.length / 4 - minOf(s.length / 4, res))
}


fun main() {
    while (true) {
        val n = (readlnOrNull() ?: return).split(" ")[0].toInt()
        val d = List(n) { readLn() }
        println("${d.sumOf { solveMin(it) }} ${d.sumOf { solveMax(it) }}")
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }