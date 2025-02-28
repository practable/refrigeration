<template>
  <div>
      <div v-html="renderedMarkdown"></div>
  </div>
</template>

<script>
import "katex/dist/katex.min.css";
// import MarkdownIt from 'markdown-it';
// import markdownItKatex from "markdown-it-katex";
import renderMarkdown from "@/utils/markdownRenderer";


export default {
  name: 'MarkdownRender',
  props: {
      content: {
          type: String,
          required: true,
      }
  },
  data() {
      return {
          testData: `# Math Example Here is some math rendered with KaTeX: Inline: $E = mc^2$ Block:\n\n\\[\nN_{Nu,f} = b(N_{Gr,Nu})^n\n\\]\n\n

                      \\frac{1}{\\sqrt{2\\pi\\sigma^2}} e^{-\\frac{(x-\\mu)^2}{2\\sigma^2}}

                      $$a^2 + b^2 = c^2$$
                      Here is an inline formula: \\( E = mc^2 \\)

                      Here is a block formula:
                      \\[N_{Nu,f} = b(N_{Gr,Nu})^n\\]

                      
                      `,

          // markdownItInstance: null,
      };
  },

  // created() {
  //     // Initialize the Markdown-It renderer with KaTeX
  //     this.markdownItInstance = new MarkdownIt({
  //         html: true,
  //         linkify: true,
  //         typographer: true,
  //     }).use(markdownItKatex);
  // },

  computed: {
      renderedMarkdown() {
          return renderMarkdown(this.content);
      },


  },
  methods: {

  },
};
</script>

<style>
/* Center align block math */
.katex-display {
  text-align: center;
  margin: 1em 0;
}

/* Ensure inline math aligns with text */
.katex {
  vertical-align: middle;
}

/* Optional: Adjust font sizes if needed */
.katex .base {
  font-size: 1em;
}
</style>