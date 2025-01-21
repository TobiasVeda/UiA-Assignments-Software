using System.ComponentModel.DataAnnotations;

namespace assignment_4.Models;

public class Blog{
    
    public int Id{ get; set; }

    [Required] [Display(Name = "Nickname")]
    public string Nickname{ get; set; } = string.Empty;

    [Required] [StringLength(50)] [Display(Name = "Title")]
    public string Title{ get; set; } = string.Empty;
    
    [Required] [StringLength(200)] [Display(Name = "Summary")]
    public string Summary{ get; set; } = string.Empty;

    [Required] [StringLength(2000)] [Display(Name = "Content")]
    public string Content{ get; set; } = string.Empty;
    
    [Display(Name = "Timestamp")]
    public DateTime Time{ get; set; }
    
    public Blog(){}
    public Blog(string nickname, string title, string summary, string content, DateTime time){
        // used for initializer
        Nickname = nickname;
        Title = title;
        Summary = summary;
        Content = content;
        Time = time;
    }
}
