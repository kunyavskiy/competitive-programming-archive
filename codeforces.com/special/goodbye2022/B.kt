private fun solve() {
    val (n, k) = readInts()
    val x = List(n) {
            if (it % 2 == 1) {
               it / 2 + 1
            } else {
                n - (it / 2)
            }
        }
    //System.err.println(x.windowed(k).map { it.max() + it.min() }.max())
    println(x.joinToString(" "))
}

fun main() {
    repeat(readInt()) {
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }