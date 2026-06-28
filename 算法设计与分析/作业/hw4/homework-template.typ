#let theme = (
  main_blue: rgb("#224870"),
  light_blue: rgb("#F1F6FC"),
  line_gray: rgb("#D2DAE4"),
  text_gray: rgb("#5A626C"),
)

#let answer_box(body) = rect(
  width: 100%,
  fill: white,
  stroke: 0.5pt + theme.line_gray,
  radius: 2mm,
  inset: (x: 1em, y: 1em),
  body,
)

#let solution(body) = answer_box[
  *解：*

  #body
]

#let info_box(
  student_name: [],
  student_id: [],
  class_name: [],
  teacher: [],
  due_date: [],
) = rect(
  width: 100%,
  fill: theme.light_blue,
  stroke: 0.6pt + theme.main_blue,
  radius: 2mm,
  inset: (x: 1.2em, y: 0.8em),
  grid(
    columns: (2.2cm, 1fr, 2.2cm, 1fr),
    column-gutter: 0.9em,
    row-gutter: 1em,
    align: left,
    [*姓名*], [#student_name], [*学号*], [#student_id],
    [*班级*], [#class_name], [*教师*], [#teacher],
    [*提交日期*], [#due_date], [], [],
  ),
)


#let homework_template(
  header_title: [课程作业],
  course: [课程名称],
  homework_title: [第 1 次作业],
  student_name: [你的姓名],
  student_id: [2024110000],
  class_name: [你的班级],
  teacher: [任课教师],
  due_date: [2026 年 3 月 19 日],
  body_font: ("Times New Roman", "SimSun"),
  heading_font: ("Times New Roman", "SimHei"),
  doc,
) = {
  set page(
    paper: "a4",
    margin: 2.2cm,
    header: context {
      set text(size: 9pt, fill: theme.text_gray)
      [
        #header_title#h(1fr)#counter(page).display("1/1", both: true)

        #line(length: 100%, stroke: 0.4pt + theme.line_gray)

        #v(2em)
      ]
    },
    header-ascent: 0pt,
    footer: none,
  )

  set text(
    font: body_font,
    size: 12pt,
    lang: "zh",
  )
  set par(
    first-line-indent: 2em,
    spacing: 1em,
    leading: 0.45em,
  )
  set heading(numbering: "1.1")

  show heading.where(level: 1): it => block(above: 2em, below: 0.6em)[
    #set text(
      font: heading_font,
      size: 18pt,
      weight: "bold",
      fill: theme.main_blue,
    )
    #it
  ]

  show heading.where(level: 2): it => block(above: 1em, below: 1em)[
    #set text(
      font: heading_font,
      size: 15pt,
      weight: "bold",
      fill: theme.main_blue,
    )
    #it
  ]

  align(center)[
    #set par(first-line-indent: 1pt)
    #set text(font: heading_font)

    #v(1em)
    #text(
      size: 22pt,
      weight: "bold",
      fill: theme.main_blue,
    )[#homework_title]

    #v(0.20em)
    #text(size: 16pt)[#course]

    #v(1em)
    #line(length: 90%, stroke: 0.8pt + theme.line_gray)
  ]

  v(1em)
  info_box(
    student_name: student_name,
    student_id: student_id,
    class_name: class_name,
    teacher: teacher,
    due_date: due_date,
  )

  v(0em)
  doc
}
