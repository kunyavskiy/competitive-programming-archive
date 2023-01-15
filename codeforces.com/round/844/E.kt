data class Rectangle(var l:Int, var r:Int, var u:Int, var d:Int, val id:Int) {
    fun remove() {
        l = 0
        r = 0
        u = 0
        d = 0
    }
}

inline fun removeIntersections(data: List<Rectangle>, filter: (Rectangle) -> Boolean, onRemove : (Rectangle) -> Unit) : List<Rectangle> {
    val (yes, no) = data.partition(filter)
    var cur: Rectangle? = null
    for (r in yes.sortedBy { it.l }) {
        val prev = cur?.takeIf { it.r > r.l }
        if (prev == null) {
            cur = r
        } else if (prev.r >= r.r) {
            onRemove(r)
        } else if (prev.l == r.l) {
            onRemove(prev)
            cur = r
        } else {
            if (prev.d - prev.u <= r.d - r.u) {
                prev.r = r.l
            } else {
                r.l = prev.r
            }
            require(prev.r != prev.l)
            require(r.l != r.r)
            cur = r
        }
    }
    return yes + no
}

private fun solve() {
    var data = List(readInt()) {
        val (u, l, d, r) = readInts()
        Rectangle(l, r + 1, u, d, it)
    }

    data = removeIntersections(data, { it.u == 1 && it.d == 2 }) { it.remove() }
    data = removeIntersections(data, { it.u == 1 && it.d == 1 }) { it.remove() }
    data = removeIntersections(data, { it.u == 1 }) {
        if (it.d == 2) {
            it.u = 2
        } else {
            it.remove()
        }
    }
    data = removeIntersections(data, { it.u == 2 && it.d == 2 }) { it.remove() }
    data = removeIntersections(data, { it.d == 2 }) {
        if (it.u == 1) {
            it.d = 1
        } else {
            it.remove()
        }
    }
    data = removeIntersections(data, { it.u == 1 && it.d == 1 }) { it.remove() }
    data = removeIntersections(data, { it.u == 2 && it.d == 2 }) { it.remove() }
    data = data.sortedBy { it.id }
    println(data.sumOf { (it.d - it.u + 1).toLong() * (it.r - it.l) })
    for (i in data) {
        if (i.u == 0) {
            println("0 0 0 0")
        } else {
            println("${i.u} ${i.l} ${i.d} ${i.r - 1}")
        }
    }
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