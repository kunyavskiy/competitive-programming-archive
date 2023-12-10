import kotlin.math.sqrt

private operator fun <T> List<T>.component6() = get(5)
private operator fun <T> List<T>.component7() = get(6)
private fun solve() {
    val (xa_, ya_, xb_, yb_, xc, yc, r) = readInts().map { it.toDouble() }
    val xa = xa_ - xc
    val xb = xb_ - xc
    val ya = ya_ - yc
    val yb = yb_ - yc

    if (inside(xa, ya, r) != inside(xb, yb, r)) {
        println(dist(xa, ya, xb, yb))
    } else if (xa != 0.0 || ya != 0.0) {
        val (xo, yo) = invert(xa, ya, r)
        val (xi, yi) = intersect(xo, yo, xb, yb, r)
        println("$xi $yi")
        println(dist(xa, ya, xi, yi) + dist(xb, yb, xi, yi))
    } else {
        val (xo, yo) = invert(xb, yb, r)
        val (xi, yi) = intersect(xo, yo, xa, ya, r)
        println(dist(xa, ya, xi, yi) + dist(xb, yb, xi, yi))
    }
}

fun intersect(x1: Double, y1: Double, x2: Double, y2:Double, r: Double) : Pair<Double, Double> {
    val vx = x2 - x1
    val vy = y2 - y1
    val A = vx * vx + vy * vy
    val B = 2 * x1 * vx + 2 * y1 * vy
    val C = x1 * x1 + y1 * y1 - r * r
    val t = (-B + sqrt(B * B - 4 * A * C)) / (2 * A)
    return (x1 + vx * t) to (y1 + vy * t)
}

fun invert(x: Double, y: Double, r: Double): Pair<Double, Double> {
    val d = dist2(x, y)
    return (x * r * r / d) to (y * r * r / d)
}

fun dist(x1: Double, y1: Double, x2:Double, y2:Double) = sqrt(dist2(x1 - x2, y1 - y2))
fun dist2(x: Double, y: Double) = x * x + y * y
fun inside(x: Double, y: Double, r: Double) = dist2(x, y) <= r * r

fun main() {
    val t = readInt()
    repeat(t) {
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }